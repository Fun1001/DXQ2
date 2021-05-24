/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioServer;
    QRadioButton *radioClient;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAddr;
    QLineEdit *EditIP;
    QLabel *label_2;
    QLineEdit *EditPort;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnConn;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *EditRecv;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkHexDisp;
    QPushButton *BtnClearRecv;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *EditSend;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkHexSend;
    QPushButton *BtnSend;
    QSpacerItem *verticalSpacer_2;
    QComboBox *cbLstClients;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QLabel *label_13;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *edit_gz;
    QLabel *label_23;
    QLabel *label_22;
    QLabel *label_3;
    QLineEdit *edit_temp;
    QLineEdit *edit_az;
    QLabel *label_21;
    QLabel *label_6;
    QLabel *label_4;
    QLineEdit *edit_gy;
    QLineEdit *edit_ax;
    QLabel *label_5;
    QLineEdit *edit_gx;
    QLineEdit *edit_ay;
    QLabel *label_24;
    QLineEdit *edit_pitch;
    QLineEdit *edit_roll;
    QLineEdit *edit_yaw;
    QLineEdit *edit_warn;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *spin_uptime;
    QPushButton *btn_setpara;
    QComboBox *cmb_mpustep;
    QSpinBox *spin_templmt;
    QLabel *label_25;
    QLabel *label_26;
    QPushButton *btn_readpara;
    QLabel *label_27;
    QLabel *label_28;
    QSpinBox *spin_warntime;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(934, 661);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(9);
        tabWidget->setFont(font);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(16777215, 350));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(0, 60));
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioServer = new QRadioButton(groupBox_4);
        radioServer->setObjectName(QString::fromUtf8("radioServer"));

        horizontalLayout_4->addWidget(radioServer);

        radioClient = new QRadioButton(groupBox_4);
        radioClient->setObjectName(QString::fromUtf8("radioClient"));

        horizontalLayout_4->addWidget(radioClient);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(groupBox_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelAddr = new QLabel(groupBox_2);
        labelAddr->setObjectName(QString::fromUtf8("labelAddr"));

        horizontalLayout_5->addWidget(labelAddr);

        EditIP = new QLineEdit(groupBox_2);
        EditIP->setObjectName(QString::fromUtf8("EditIP"));
        EditIP->setMinimumSize(QSize(300, 20));

        horizontalLayout_5->addWidget(EditIP);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        EditPort = new QLineEdit(groupBox_2);
        EditPort->setObjectName(QString::fromUtf8("EditPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(EditPort->sizePolicy().hasHeightForWidth());
        EditPort->setSizePolicy(sizePolicy1);
        EditPort->setMinimumSize(QSize(140, 20));
        EditPort->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(EditPort);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnConn = new QPushButton(groupBox_2);
        BtnConn->setObjectName(QString::fromUtf8("BtnConn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BtnConn->sizePolicy().hasHeightForWidth());
        BtnConn->setSizePolicy(sizePolicy2);
        BtnConn->setMinimumSize(QSize(120, 0));
        BtnConn->setMaximumSize(QSize(10000, 16777215));

        horizontalLayout->addWidget(BtnConn);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        EditRecv = new QTextEdit(groupBox);
        EditRecv->setObjectName(QString::fromUtf8("EditRecv"));
        EditRecv->setReadOnly(true);
        EditRecv->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(EditRecv);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chkHexDisp = new QCheckBox(groupBox);
        chkHexDisp->setObjectName(QString::fromUtf8("chkHexDisp"));

        verticalLayout_2->addWidget(chkHexDisp);

        BtnClearRecv = new QPushButton(groupBox);
        BtnClearRecv->setObjectName(QString::fromUtf8("BtnClearRecv"));
        BtnClearRecv->setMinimumSize(QSize(120, 0));

        verticalLayout_2->addWidget(BtnClearRecv);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_5->addWidget(groupBox);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 150));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        EditSend = new QTextEdit(groupBox_3);
        EditSend->setObjectName(QString::fromUtf8("EditSend"));

        horizontalLayout_3->addWidget(EditSend);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        chkHexSend = new QCheckBox(groupBox_3);
        chkHexSend->setObjectName(QString::fromUtf8("chkHexSend"));

        verticalLayout_3->addWidget(chkHexSend);

        BtnSend = new QPushButton(groupBox_3);
        BtnSend->setObjectName(QString::fromUtf8("BtnSend"));
        BtnSend->setMinimumSize(QSize(120, 0));

        verticalLayout_3->addWidget(BtnSend);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        cbLstClients = new QComboBox(groupBox_3);
        cbLstClients->setObjectName(QString::fromUtf8("cbLstClients"));
        cbLstClients->setMinimumSize(QSize(120, 0));

        verticalLayout_3->addWidget(cbLstClients);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_5->addWidget(groupBox_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(16);
        groupBox_5->setFont(font2);
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font2);
        label_13->setLayoutDirection(Qt::LeftToRight);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 5, 0, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font2);
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 4, 0, 1, 1);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font2);
        label_12->setLayoutDirection(Qt::LeftToRight);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 6, 0, 1, 1);

        edit_gz = new QLineEdit(groupBox_5);
        edit_gz->setObjectName(QString::fromUtf8("edit_gz"));
        edit_gz->setReadOnly(true);

        gridLayout->addWidget(edit_gz, 6, 1, 1, 1);

        label_23 = new QLabel(groupBox_5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font2);
        label_23->setLayoutDirection(Qt::LeftToRight);
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_23, 7, 0, 1, 1);

        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font2);
        label_22->setLayoutDirection(Qt::LeftToRight);
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_22, 8, 0, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        edit_temp = new QLineEdit(groupBox_5);
        edit_temp->setObjectName(QString::fromUtf8("edit_temp"));
        edit_temp->setReadOnly(true);

        gridLayout->addWidget(edit_temp, 0, 1, 1, 1);

        edit_az = new QLineEdit(groupBox_5);
        edit_az->setObjectName(QString::fromUtf8("edit_az"));
        edit_az->setReadOnly(true);

        gridLayout->addWidget(edit_az, 3, 1, 1, 1);

        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font2);
        label_21->setLayoutDirection(Qt::LeftToRight);
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_21, 9, 0, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        edit_gy = new QLineEdit(groupBox_5);
        edit_gy->setObjectName(QString::fromUtf8("edit_gy"));
        edit_gy->setReadOnly(true);

        gridLayout->addWidget(edit_gy, 5, 1, 1, 1);

        edit_ax = new QLineEdit(groupBox_5);
        edit_ax->setObjectName(QString::fromUtf8("edit_ax"));
        edit_ax->setReadOnly(true);

        gridLayout->addWidget(edit_ax, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        edit_gx = new QLineEdit(groupBox_5);
        edit_gx->setObjectName(QString::fromUtf8("edit_gx"));
        edit_gx->setReadOnly(true);

        gridLayout->addWidget(edit_gx, 4, 1, 1, 1);

        edit_ay = new QLineEdit(groupBox_5);
        edit_ay->setObjectName(QString::fromUtf8("edit_ay"));
        edit_ay->setReadOnly(true);

        gridLayout->addWidget(edit_ay, 2, 1, 1, 1);

        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font2);
        label_24->setLayoutDirection(Qt::LeftToRight);
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_24, 10, 0, 1, 1);

        edit_pitch = new QLineEdit(groupBox_5);
        edit_pitch->setObjectName(QString::fromUtf8("edit_pitch"));
        edit_pitch->setReadOnly(true);

        gridLayout->addWidget(edit_pitch, 7, 1, 1, 1);

        edit_roll = new QLineEdit(groupBox_5);
        edit_roll->setObjectName(QString::fromUtf8("edit_roll"));
        edit_roll->setReadOnly(true);

        gridLayout->addWidget(edit_roll, 8, 1, 1, 1);

        edit_yaw = new QLineEdit(groupBox_5);
        edit_yaw->setObjectName(QString::fromUtf8("edit_yaw"));
        edit_yaw->setReadOnly(true);

        gridLayout->addWidget(edit_yaw, 9, 1, 1, 1);

        edit_warn = new QLineEdit(groupBox_5);
        edit_warn->setObjectName(QString::fromUtf8("edit_warn"));
        edit_warn->setReadOnly(true);

        gridLayout->addWidget(edit_warn, 10, 1, 1, 1);


        verticalLayout_6->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFont(font2);
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        spin_uptime = new QDoubleSpinBox(groupBox_6);
        spin_uptime->setObjectName(QString::fromUtf8("spin_uptime"));
        spin_uptime->setDecimals(1);
        spin_uptime->setMinimum(0.100000000000000);
        spin_uptime->setMaximum(10.000000000000000);
        spin_uptime->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(spin_uptime, 2, 3, 1, 1);

        btn_setpara = new QPushButton(groupBox_6);
        btn_setpara->setObjectName(QString::fromUtf8("btn_setpara"));
        btn_setpara->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(btn_setpara, 3, 2, 1, 2);

        cmb_mpustep = new QComboBox(groupBox_6);
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->setObjectName(QString::fromUtf8("cmb_mpustep"));

        gridLayout_4->addWidget(cmb_mpustep, 0, 3, 1, 1);

        spin_templmt = new QSpinBox(groupBox_6);
        spin_templmt->setObjectName(QString::fromUtf8("spin_templmt"));
        spin_templmt->setValue(30);

        gridLayout_4->addWidget(spin_templmt, 0, 1, 1, 1);

        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_25, 0, 0, 1, 1);

        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_26, 0, 2, 1, 1);

        btn_readpara = new QPushButton(groupBox_6);
        btn_readpara->setObjectName(QString::fromUtf8("btn_readpara"));
        btn_readpara->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(btn_readpara, 3, 0, 1, 2);

        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_27, 2, 2, 1, 1);

        label_28 = new QLabel(groupBox_6);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_28, 2, 0, 1, 1);

        spin_warntime = new QSpinBox(groupBox_6);
        spin_warntime->setObjectName(QString::fromUtf8("spin_warntime"));
        spin_warntime->setMaximum(60);
        spin_warntime->setValue(30);

        gridLayout_4->addWidget(spin_warntime, 2, 1, 1, 1);


        verticalLayout_6->addWidget(groupBox_6);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_4->addWidget(tabWidget);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Qt\347\275\221\347\273\234\350\260\203\350\257\225\345\212\251\346\211\213    by 18041820\345\255\231\346\230\212\347\204\266 18041811\346\226\271\344\271\235\345\267\235", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\347\275\221\347\273\234\350\256\276\347\275\256", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
        radioServer->setText(QCoreApplication::translate("MainWindow", "TCP\346\234\215\345\212\241\345\231\250", nullptr));
        radioClient->setText(QCoreApplication::translate("MainWindow", "TCP\345\256\242\346\210\267\347\253\257", nullptr));
        labelAddr->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        EditIP->setText(QCoreApplication::translate("MainWindow", "192.168.", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        EditPort->setText(QCoreApplication::translate("MainWindow", "4321", nullptr));
        BtnConn->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", nullptr));
        chkHexDisp->setText(QCoreApplication::translate("MainWindow", "HEX\346\230\276\347\244\272", nullptr));
        BtnClearRecv->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", nullptr));
        chkHexSend->setText(QCoreApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        BtnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\347\275\221\347\273\234\350\260\203\350\257\225", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\347\233\221\346\265\213\346\225\260\346\215\256", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\350\247\222\351\200\237\345\272\246gy\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\350\247\222\351\200\237\345\272\246gx\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\350\247\222\351\200\237\345\272\246gz\357\274\232", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\344\277\257\344\273\260\350\247\222\357\274\232", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\346\250\252\346\273\232\350\247\222\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", " \346\270\251\345\272\246\357\274\232", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\350\210\252\345\220\221\350\247\222\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246az\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246ax\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246ay\357\274\232", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\347\212\266\346\200\201\357\274\232", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", " \345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        spin_uptime->setSuffix(QCoreApplication::translate("MainWindow", "\347\247\222", nullptr));
        btn_setpara->setText(QCoreApplication::translate("MainWindow", " \350\256\276\347\275\256\345\217\202\346\225\260", nullptr));
        cmb_mpustep->setItemText(0, QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        cmb_mpustep->setItemText(1, QCoreApplication::translate("MainWindow", "1\347\272\247", nullptr));
        cmb_mpustep->setItemText(2, QCoreApplication::translate("MainWindow", "2\347\272\247", nullptr));
        cmb_mpustep->setItemText(3, QCoreApplication::translate("MainWindow", "3\347\272\247", nullptr));
        cmb_mpustep->setItemText(4, QCoreApplication::translate("MainWindow", "4\347\272\247", nullptr));
        cmb_mpustep->setItemText(5, QCoreApplication::translate("MainWindow", "5\347\272\247", nullptr));
        cmb_mpustep->setItemText(6, QCoreApplication::translate("MainWindow", "6\347\272\247", nullptr));
        cmb_mpustep->setItemText(7, QCoreApplication::translate("MainWindow", "7\347\272\247", nullptr));
        cmb_mpustep->setItemText(8, QCoreApplication::translate("MainWindow", "8\347\272\247", nullptr));
        cmb_mpustep->setItemText(9, QCoreApplication::translate("MainWindow", "9\347\272\247", nullptr));
        cmb_mpustep->setItemText(10, QCoreApplication::translate("MainWindow", "10\347\272\247", nullptr));

        cmb_mpustep->setCurrentText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        spin_templmt->setSuffix(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        spin_templmt->setPrefix(QString());
        label_25->setText(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246\344\270\212\351\231\220\357\274\232", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "\351\234\207\345\212\250\347\201\265\346\225\217\345\272\246\357\274\232", nullptr));
        btn_readpara->setText(QCoreApplication::translate("MainWindow", " \350\257\273\345\217\226\345\217\202\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240\346\227\266\351\227\264\351\227\264\351\232\224\357\274\232", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\346\227\266\351\225\277\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\351\230\262\347\201\253\351\230\262\347\233\227\346\243\200\346\265\213\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
