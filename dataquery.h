#ifndef DATAQUERY_H
#define DATAQUERY_H

#include <QMap>
#include <QVector>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include <cmath>

class DataQuery {
private:
    QMap<int, QMap<double, int>> dataMap;
    QList<int> firstColumnValues;
    QMap<int, QList<double>> thirdColumnValues;

public:
    bool loadData(const QString& filename);

    // 精确查询
    int query(int firstColumn, double thirdColumn);

    // 双线性插值计算
    double interpolate(int firstColumn, double thirdColumn);

private:
    // 查找第一列的上下边界
    void findFirstColumnBounds(int targetFirst, int& lower, int& upper);
    // 在第三列方向进行线性插值
    double interpolateInThirdDirection(int firstColumn, double targetThird);


public:
    // 获取数据范围信息
    void printDataRange();

};
#endif // DATAQUERY_H
