#include "txtworker.h"

txtworker::txtworker(QObject *parent) : QObject(parent)
{

}

void txtworker::starting(QString filepath, QString pindian1, QString pinpian1, QString tiaozhi1,
                         QString gonglv1, QString malv1, QString zhenchang1, QString zhenmazu1,
                         QString fuzhenfangshi1, QString fuzhenchang1, QString maxing1,
                         QString bianmaweizhi1, QString pindian2, QString pinpian2, QString tiaozhi2,
                         QString gonglv2, QString malv2, QString zhenchang2, QString zhenmazu2,
                         QString fuzhenfangshi2, QString fuzhenchang2, QString maxing2, QString bianmaweizhi2)
{
    txtfile.setFileName(filepath+ "/发射机配置文件" + ".txt");
    txtfile.open(QIODevice::WriteOnly | QIODevice::Text);


    txtfile.write("发射机1配置参数\n");
    txtfile.write(QString("频点: %1\n").arg(pindian1).toUtf8());
    txtfile.write(QString("频偏: %1\n").arg(pinpian1).toUtf8());
    txtfile.write(QString("调制: %1\n").arg(tiaozhi1).toUtf8());
    txtfile.write(QString("功率: %1\n").arg(gonglv1).toUtf8());
    txtfile.write(QString("码率: %1\n").arg(malv1).toUtf8());
    txtfile.write(QString("帧长: %1\n").arg(zhenchang1).toUtf8());
    txtfile.write(QString("帧码组: %1\n").arg(zhenmazu1).toUtf8());
    txtfile.write(QString("副帧方式: %1\n").arg(fuzhenfangshi1).toUtf8());
    txtfile.write(QString("副帧长: %1\n").arg(fuzhenchang1).toUtf8());
    txtfile.write(QString("码型: %1\n").arg(maxing1).toUtf8());
    txtfile.write(QString("编码位置: %1\n").arg(bianmaweizhi1).toUtf8());

    txtfile.write("发射机2配置参数\n");
    txtfile.write(QString("频点: %1\n").arg(pindian2).toUtf8());
    txtfile.write(QString("频偏: %1\n").arg(pinpian2).toUtf8());
    txtfile.write(QString("调制: %1\n").arg(tiaozhi2).toUtf8());
    txtfile.write(QString("功率: %1\n").arg(gonglv2).toUtf8());
    txtfile.write(QString("码率: %1\n").arg(malv2).toUtf8());
    txtfile.write(QString("帧长: %1\n").arg(zhenchang2).toUtf8());
    txtfile.write(QString("帧码组: %1\n").arg(zhenmazu2).toUtf8());
    txtfile.write(QString("副帧方式: %1\n").arg(fuzhenfangshi2).toUtf8());
    txtfile.write(QString("副帧长: %1\n").arg(fuzhenchang2).toUtf8());
    txtfile.write(QString("码型: %1\n").arg(maxing2).toUtf8());
    txtfile.write(QString("编码位置: %1\n").arg(bianmaweizhi2).toUtf8());


    txtfile.close();

}
