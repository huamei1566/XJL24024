#include "dataquery.h"


bool DataQuery::loadData(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << filename;
        return false;
    }

    dataMap.clear();
    firstColumnValues.clear();
    thirdColumnValues.clear();

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(';');
        if (parts.size() != 3) continue;

        bool ok1, ok2, ok3;
        int col1 = parts[0].toDouble(&ok1)*1000;
        int col2 = parts[1].toInt(&ok2);
        double col3 = parts[2].toDouble(&ok3);

        if (ok1 && ok2 && ok3) {
            dataMap[col1][col3] = col2;
        }
    }
    file.close();

    // 预处理排序数据
    firstColumnValues = dataMap.keys();  // 现在可以正常赋值
    std::sort(firstColumnValues.begin(), firstColumnValues.end());

    for (int firstCol : firstColumnValues) {
        QList<double> thirdCols = dataMap[firstCol].keys();
        std::sort(thirdCols.begin(), thirdCols.end());
        thirdColumnValues[firstCol] = thirdCols;
    }

    qDebug() << "数据加载完成，共" << firstColumnValues.size() << "个第一列值";
    return true;
}

int DataQuery::query(int firstColumn, double thirdColumn)
{
    if (dataMap.contains(firstColumn) && dataMap[firstColumn].contains(thirdColumn)) {
        return dataMap[firstColumn][thirdColumn];
    }
    return -1;
}

double DataQuery::interpolate(int firstColumn, double thirdColumn)
{
    // 1. 查找第一列的边界
    int firstLower = -1, firstUpper = -1;
    findFirstColumnBounds(firstColumn, firstLower, firstUpper);

    if (firstLower == -1 || firstUpper == -1) {
        qDebug() << "无法找到合适的边界进行插值";
        return 0.0;
    }

    // 2. 如果第一列正好存在，只需在第三列方向插值
    if (firstLower == firstUpper) {
        return interpolateInThirdDirection(firstLower, thirdColumn);
    }

    // 3. 双线性插值
    double valueAtLowerFirst = interpolateInThirdDirection(firstLower, thirdColumn);
    double valueAtUpperFirst = interpolateInThirdDirection(firstUpper, thirdColumn);

    // 计算在第一列方向的权重
    double weight = static_cast<double>(firstColumn - firstLower) /
                   (firstUpper - firstLower);

    return valueAtLowerFirst + weight * (valueAtUpperFirst - valueAtLowerFirst);
}

void DataQuery::findFirstColumnBounds(int targetFirst, int &lower, int &upper)
{
    if (firstColumnValues.isEmpty()) {
        lower = upper = -1;
        return;
    }

    // 如果正好存在
    if (firstColumnValues.contains(targetFirst)) {
        lower = upper = targetFirst;
        return;
    }

    // 查找边界
    auto it = std::lower_bound(firstColumnValues.begin(), firstColumnValues.end(), targetFirst);

    if (it == firstColumnValues.begin()) {
        // 目标值小于所有现有值
        lower = upper = firstColumnValues.first();
    } else if (it == firstColumnValues.end()) {
        // 目标值大于所有现有值
        lower = upper = firstColumnValues.last();
    } else {
        upper = *it;
        lower = *(it - 1);
    }
}

double DataQuery::interpolateInThirdDirection(int firstColumn, double targetThird)
{
    if (!thirdColumnValues.contains(firstColumn) ||
        thirdColumnValues[firstColumn].isEmpty()) {
        return 0.0;
    }

    const QList<double>& thirdCols = thirdColumnValues[firstColumn];

    // 如果正好存在
    if (dataMap[firstColumn].contains(targetThird)) {
        return dataMap[firstColumn][targetThird];
    }

    // 查找第三列的上下边界
    auto it = std::lower_bound(thirdCols.begin(), thirdCols.end(), targetThird);

    double thirdLower, thirdUpper;
    if (it == thirdCols.begin()) {
        thirdLower = thirdUpper = thirdCols.first();
    } else if (it == thirdCols.end()) {
        thirdLower = thirdUpper = thirdCols.last();
    } else {
        thirdUpper = *it;
        thirdLower = *(it - 1);
    }

    // 如果边界相同（在端点处）
    if (thirdLower == thirdUpper) {
        return dataMap[firstColumn][thirdLower];
    }

    // 线性插值
    double valueLower = dataMap[firstColumn][thirdLower];
    double valueUpper = dataMap[firstColumn][thirdUpper];

    double weight = (targetThird - thirdLower) / (thirdUpper - thirdLower);
    return valueLower + weight * (valueUpper - valueLower);
}

void DataQuery::printDataRange()
{
    if (firstColumnValues.isEmpty()) {
        qDebug() << "没有数据";
        return;
    }
}
