/****************************************************************************
** Meta object code from reading C++ file 'videowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../videowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FFmpegsThread_t {
    QByteArrayData data[20];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFmpegsThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFmpegsThread_t qt_meta_stringdata_FFmpegsThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FFmpegsThread"
QT_MOC_LITERAL(1, 14, 12), // "receiveImage"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "image"
QT_MOC_LITERAL(4, 34, 18), // "getVideoResolution"
QT_MOC_LITERAL(5, 53, 11), // "nResolution"
QT_MOC_LITERAL(6, 65, 4), // "int*"
QT_MOC_LITERAL(7, 70, 5), // "width"
QT_MOC_LITERAL(8, 76, 6), // "height"
QT_MOC_LITERAL(9, 83, 4), // "init"
QT_MOC_LITERAL(10, 88, 5), // "INT64"
QT_MOC_LITERAL(11, 94, 6), // "handle"
QT_MOC_LITERAL(12, 101, 10), // "Resolution"
QT_MOC_LITERAL(13, 112, 12), // "VideoWidget*"
QT_MOC_LITERAL(14, 125, 7), // "pWidget"
QT_MOC_LITERAL(15, 133, 4), // "free"
QT_MOC_LITERAL(16, 138, 4), // "play"
QT_MOC_LITERAL(17, 143, 5), // "pause"
QT_MOC_LITERAL(18, 149, 4), // "next"
QT_MOC_LITERAL(19, 154, 4) // "stop"

    },
    "FFmpegsThread\0receiveImage\0\0image\0"
    "getVideoResolution\0nResolution\0int*\0"
    "width\0height\0init\0INT64\0handle\0"
    "Resolution\0VideoWidget*\0pWidget\0free\0"
    "play\0pause\0next\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFmpegsThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   57,    2, 0x0a /* Public */,
       9,    3,   64,    2, 0x0a /* Public */,
      15,    0,   71,    2, 0x0a /* Public */,
      16,    0,   72,    2, 0x0a /* Public */,
      17,    0,   73,    2, 0x0a /* Public */,
      18,    0,   74,    2, 0x0a /* Public */,
      19,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 6,    5,    7,    8,
    QMetaType::Bool, 0x80000000 | 10, QMetaType::Int, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FFmpegsThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FFmpegsThread *_t = static_cast<FFmpegsThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->getVideoResolution((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 2: { bool _r = _t->init((*reinterpret_cast< INT64(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< VideoWidget*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->free(); break;
        case 4: _t->play(); break;
        case 5: _t->pause(); break;
        case 6: _t->next(); break;
        case 7: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VideoWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FFmpegsThread::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegsThread::receiveImage)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FFmpegsThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FFmpegsThread.data,
      qt_meta_data_FFmpegsThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FFmpegsThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFmpegsThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FFmpegsThread.stringdata0))
        return static_cast<void*>(const_cast< FFmpegsThread*>(this));
    return QThread::qt_metacast(_clname);
}

int FFmpegsThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FFmpegsThread::receiveImage(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VideoWidget_t {
    QByteArrayData data[163];
    char stringdata0[1851];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoWidget_t qt_meta_stringdata_VideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoWidget"
QT_MOC_LITERAL(1, 12, 16), // "receivePlayStart"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "receivePlayError"
QT_MOC_LITERAL(4, 47, 16), // "receivePlayFinsh"
QT_MOC_LITERAL(5, 64, 12), // "receiveImage"
QT_MOC_LITERAL(6, 77, 5), // "image"
QT_MOC_LITERAL(7, 83, 8), // "fileDrag"
QT_MOC_LITERAL(8, 92, 3), // "url"
QT_MOC_LITERAL(9, 96, 10), // "btnClicked"
QT_MOC_LITERAL(10, 107, 7), // "objName"
QT_MOC_LITERAL(11, 115, 17), // "pushVideoh264Data"
QT_MOC_LITERAL(12, 133, 12), // "MP_DATA_INFO"
QT_MOC_LITERAL(13, 146, 5), // "pData"
QT_MOC_LITERAL(14, 152, 11), // "updateImage"
QT_MOC_LITERAL(15, 164, 10), // "checkVideo"
QT_MOC_LITERAL(16, 175, 9), // "getLength"
QT_MOC_LITERAL(17, 185, 11), // "getPosition"
QT_MOC_LITERAL(18, 197, 11), // "setPosition"
QT_MOC_LITERAL(19, 209, 8), // "position"
QT_MOC_LITERAL(20, 218, 7), // "getMute"
QT_MOC_LITERAL(21, 226, 7), // "setMute"
QT_MOC_LITERAL(22, 234, 4), // "mute"
QT_MOC_LITERAL(23, 239, 9), // "getVolume"
QT_MOC_LITERAL(24, 249, 9), // "setVolume"
QT_MOC_LITERAL(25, 259, 6), // "volume"
QT_MOC_LITERAL(26, 266, 11), // "setInterval"
QT_MOC_LITERAL(27, 278, 8), // "interval"
QT_MOC_LITERAL(28, 287, 12), // "setSleepTime"
QT_MOC_LITERAL(29, 300, 9), // "sleepTime"
QT_MOC_LITERAL(30, 310, 12), // "setCheckTime"
QT_MOC_LITERAL(31, 323, 9), // "checkTime"
QT_MOC_LITERAL(32, 333, 12), // "setCheckConn"
QT_MOC_LITERAL(33, 346, 9), // "checkConn"
QT_MOC_LITERAL(34, 356, 6), // "setUrl"
QT_MOC_LITERAL(35, 363, 11), // "setHardware"
QT_MOC_LITERAL(36, 375, 8), // "hardware"
QT_MOC_LITERAL(37, 384, 11), // "setSaveFile"
QT_MOC_LITERAL(38, 396, 8), // "saveFile"
QT_MOC_LITERAL(39, 405, 15), // "setSaveInterval"
QT_MOC_LITERAL(40, 421, 12), // "saveInterval"
QT_MOC_LITERAL(41, 434, 11), // "setSavePath"
QT_MOC_LITERAL(42, 446, 8), // "savePath"
QT_MOC_LITERAL(43, 455, 11), // "setFileName"
QT_MOC_LITERAL(44, 467, 8), // "fileName"
QT_MOC_LITERAL(45, 476, 12), // "setCopyImage"
QT_MOC_LITERAL(46, 489, 9), // "copyImage"
QT_MOC_LITERAL(47, 499, 12), // "setCheckLive"
QT_MOC_LITERAL(48, 512, 9), // "checkLive"
QT_MOC_LITERAL(49, 522, 12), // "setDrawImage"
QT_MOC_LITERAL(50, 535, 9), // "drawImage"
QT_MOC_LITERAL(51, 545, 12), // "setFillImage"
QT_MOC_LITERAL(52, 558, 9), // "fillImage"
QT_MOC_LITERAL(53, 568, 13), // "setFlowEnable"
QT_MOC_LITERAL(54, 582, 10), // "flowEnable"
QT_MOC_LITERAL(55, 593, 14), // "setFlowBgColor"
QT_MOC_LITERAL(56, 608, 11), // "flowBgColor"
QT_MOC_LITERAL(57, 620, 17), // "setFlowPressColor"
QT_MOC_LITERAL(58, 638, 14), // "flowPressColor"
QT_MOC_LITERAL(59, 653, 10), // "setTimeout"
QT_MOC_LITERAL(60, 664, 7), // "timeout"
QT_MOC_LITERAL(61, 672, 14), // "setBorderWidth"
QT_MOC_LITERAL(62, 687, 11), // "borderWidth"
QT_MOC_LITERAL(63, 699, 14), // "setBorderColor"
QT_MOC_LITERAL(64, 714, 11), // "borderColor"
QT_MOC_LITERAL(65, 726, 13), // "setFocusColor"
QT_MOC_LITERAL(66, 740, 10), // "focusColor"
QT_MOC_LITERAL(67, 751, 9), // "setBgText"
QT_MOC_LITERAL(68, 761, 6), // "bgText"
QT_MOC_LITERAL(69, 768, 10), // "setBgImage"
QT_MOC_LITERAL(70, 779, 7), // "bgImage"
QT_MOC_LITERAL(71, 787, 14), // "setOSD1Visible"
QT_MOC_LITERAL(72, 802, 10), // "osdVisible"
QT_MOC_LITERAL(73, 813, 15), // "setOSD1FontSize"
QT_MOC_LITERAL(74, 829, 11), // "osdFontSize"
QT_MOC_LITERAL(75, 841, 11), // "setOSD1Text"
QT_MOC_LITERAL(76, 853, 7), // "osdText"
QT_MOC_LITERAL(77, 861, 12), // "setOSD1Color"
QT_MOC_LITERAL(78, 874, 8), // "osdColor"
QT_MOC_LITERAL(79, 883, 12), // "setOSD1Image"
QT_MOC_LITERAL(80, 896, 8), // "osdImage"
QT_MOC_LITERAL(81, 905, 13), // "setOSD1Format"
QT_MOC_LITERAL(82, 919, 9), // "OSDFormat"
QT_MOC_LITERAL(83, 929, 9), // "osdFormat"
QT_MOC_LITERAL(84, 939, 15), // "setOSD1Position"
QT_MOC_LITERAL(85, 955, 11), // "OSDPosition"
QT_MOC_LITERAL(86, 967, 11), // "osdPosition"
QT_MOC_LITERAL(87, 979, 14), // "setOSD2Visible"
QT_MOC_LITERAL(88, 994, 15), // "setOSD2FontSize"
QT_MOC_LITERAL(89, 1010, 11), // "setOSD2Text"
QT_MOC_LITERAL(90, 1022, 12), // "setOSD2Color"
QT_MOC_LITERAL(91, 1035, 12), // "setOSD2Image"
QT_MOC_LITERAL(92, 1048, 13), // "setOSD2Format"
QT_MOC_LITERAL(93, 1062, 15), // "setOSD2Position"
QT_MOC_LITERAL(94, 1078, 15), // "getHStreamCount"
QT_MOC_LITERAL(95, 1094, 15), // "pushHStreamInfo"
QT_MOC_LITERAL(96, 1110, 13), // "MP_DATA_INFO*"
QT_MOC_LITERAL(97, 1124, 14), // "getHStreamInfo"
QT_MOC_LITERAL(98, 1139, 16), // "startVideoThread"
QT_MOC_LITERAL(99, 1156, 12), // "ish265IFrame"
QT_MOC_LITERAL(100, 1169, 6), // "pParam"
QT_MOC_LITERAL(101, 1176, 16), // "setVideoh264Data"
QT_MOC_LITERAL(102, 1193, 9), // "RGB2Image"
QT_MOC_LITERAL(103, 1203, 5), // "char*"
QT_MOC_LITERAL(104, 1209, 6), // "srcBuf"
QT_MOC_LITERAL(105, 1216, 1), // "w"
QT_MOC_LITERAL(106, 1218, 1), // "h"
QT_MOC_LITERAL(107, 1220, 7), // "QImage*"
QT_MOC_LITERAL(108, 1228, 10), // "pDistImage"
QT_MOC_LITERAL(109, 1239, 8), // "isIFrame"
QT_MOC_LITERAL(110, 1248, 15), // "setVideoYUVData"
QT_MOC_LITERAL(111, 1264, 18), // "YV12ToBGR24_FFmpeg"
QT_MOC_LITERAL(112, 1283, 14), // "unsigned char*"
QT_MOC_LITERAL(113, 1298, 4), // "pYUV"
QT_MOC_LITERAL(114, 1303, 6), // "pBGR24"
QT_MOC_LITERAL(115, 1310, 5), // "width"
QT_MOC_LITERAL(116, 1316, 6), // "height"
QT_MOC_LITERAL(117, 1323, 13), // "Yuv420p2Rgb32"
QT_MOC_LITERAL(118, 1337, 5), // "pBufy"
QT_MOC_LITERAL(119, 1343, 5), // "pBufu"
QT_MOC_LITERAL(120, 1349, 5), // "pBufv"
QT_MOC_LITERAL(121, 1355, 11), // "const BYTE*"
QT_MOC_LITERAL(122, 1367, 13), // "rgbBuffer_out"
QT_MOC_LITERAL(123, 1381, 12), // "YUV420_2_RGB"
QT_MOC_LITERAL(124, 1394, 4), // "pRGB"
QT_MOC_LITERAL(125, 1399, 18), // "getVideoResolution"
QT_MOC_LITERAL(126, 1418, 11), // "nResolution"
QT_MOC_LITERAL(127, 1430, 4), // "int*"
QT_MOC_LITERAL(128, 1435, 4), // "open"
QT_MOC_LITERAL(129, 1440, 5), // "pause"
QT_MOC_LITERAL(130, 1446, 4), // "next"
QT_MOC_LITERAL(131, 1451, 5), // "close"
QT_MOC_LITERAL(132, 1457, 7), // "restart"
QT_MOC_LITERAL(133, 1465, 5), // "clear"
QT_MOC_LITERAL(134, 1471, 6), // "vtInit"
QT_MOC_LITERAL(135, 1478, 9), // "AVCodecID"
QT_MOC_LITERAL(136, 1488, 6), // "codeID"
QT_MOC_LITERAL(137, 1495, 11), // "IVideoCall*"
QT_MOC_LITERAL(138, 1507, 4), // "call"
QT_MOC_LITERAL(139, 1512, 10), // "initPacket"
QT_MOC_LITERAL(140, 1523, 11), // "osd1Visible"
QT_MOC_LITERAL(141, 1535, 12), // "osd1FontSize"
QT_MOC_LITERAL(142, 1548, 8), // "osd1Text"
QT_MOC_LITERAL(143, 1557, 9), // "osd1Color"
QT_MOC_LITERAL(144, 1567, 9), // "osd1Image"
QT_MOC_LITERAL(145, 1577, 10), // "osd1Format"
QT_MOC_LITERAL(146, 1588, 12), // "osd1Position"
QT_MOC_LITERAL(147, 1601, 11), // "osd2Visible"
QT_MOC_LITERAL(148, 1613, 12), // "osd2FontSize"
QT_MOC_LITERAL(149, 1626, 8), // "osd2Text"
QT_MOC_LITERAL(150, 1635, 9), // "osd2Color"
QT_MOC_LITERAL(151, 1645, 9), // "osd2Image"
QT_MOC_LITERAL(152, 1655, 10), // "osd2Format"
QT_MOC_LITERAL(153, 1666, 12), // "osd2Position"
QT_MOC_LITERAL(154, 1679, 14), // "OSDFormat_Text"
QT_MOC_LITERAL(155, 1694, 14), // "OSDFormat_Date"
QT_MOC_LITERAL(156, 1709, 14), // "OSDFormat_Time"
QT_MOC_LITERAL(157, 1724, 18), // "OSDFormat_DateTime"
QT_MOC_LITERAL(158, 1743, 15), // "OSDFormat_Image"
QT_MOC_LITERAL(159, 1759, 20), // "OSDPosition_Left_Top"
QT_MOC_LITERAL(160, 1780, 23), // "OSDPosition_Left_Bottom"
QT_MOC_LITERAL(161, 1804, 21), // "OSDPosition_Right_Top"
QT_MOC_LITERAL(162, 1826, 24) // "OSDPosition_Right_Bottom"

    },
    "VideoWidget\0receivePlayStart\0\0"
    "receivePlayError\0receivePlayFinsh\0"
    "receiveImage\0image\0fileDrag\0url\0"
    "btnClicked\0objName\0pushVideoh264Data\0"
    "MP_DATA_INFO\0pData\0updateImage\0"
    "checkVideo\0getLength\0getPosition\0"
    "setPosition\0position\0getMute\0setMute\0"
    "mute\0getVolume\0setVolume\0volume\0"
    "setInterval\0interval\0setSleepTime\0"
    "sleepTime\0setCheckTime\0checkTime\0"
    "setCheckConn\0checkConn\0setUrl\0setHardware\0"
    "hardware\0setSaveFile\0saveFile\0"
    "setSaveInterval\0saveInterval\0setSavePath\0"
    "savePath\0setFileName\0fileName\0"
    "setCopyImage\0copyImage\0setCheckLive\0"
    "checkLive\0setDrawImage\0drawImage\0"
    "setFillImage\0fillImage\0setFlowEnable\0"
    "flowEnable\0setFlowBgColor\0flowBgColor\0"
    "setFlowPressColor\0flowPressColor\0"
    "setTimeout\0timeout\0setBorderWidth\0"
    "borderWidth\0setBorderColor\0borderColor\0"
    "setFocusColor\0focusColor\0setBgText\0"
    "bgText\0setBgImage\0bgImage\0setOSD1Visible\0"
    "osdVisible\0setOSD1FontSize\0osdFontSize\0"
    "setOSD1Text\0osdText\0setOSD1Color\0"
    "osdColor\0setOSD1Image\0osdImage\0"
    "setOSD1Format\0OSDFormat\0osdFormat\0"
    "setOSD1Position\0OSDPosition\0osdPosition\0"
    "setOSD2Visible\0setOSD2FontSize\0"
    "setOSD2Text\0setOSD2Color\0setOSD2Image\0"
    "setOSD2Format\0setOSD2Position\0"
    "getHStreamCount\0pushHStreamInfo\0"
    "MP_DATA_INFO*\0getHStreamInfo\0"
    "startVideoThread\0ish265IFrame\0pParam\0"
    "setVideoh264Data\0RGB2Image\0char*\0"
    "srcBuf\0w\0h\0QImage*\0pDistImage\0isIFrame\0"
    "setVideoYUVData\0YV12ToBGR24_FFmpeg\0"
    "unsigned char*\0pYUV\0pBGR24\0width\0"
    "height\0Yuv420p2Rgb32\0pBufy\0pBufu\0pBufv\0"
    "const BYTE*\0rgbBuffer_out\0YUV420_2_RGB\0"
    "pRGB\0getVideoResolution\0nResolution\0"
    "int*\0open\0pause\0next\0close\0restart\0"
    "clear\0vtInit\0AVCodecID\0codeID\0IVideoCall*\0"
    "call\0initPacket\0osd1Visible\0osd1FontSize\0"
    "osd1Text\0osd1Color\0osd1Image\0osd1Format\0"
    "osd1Position\0osd2Visible\0osd2FontSize\0"
    "osd2Text\0osd2Color\0osd2Image\0osd2Format\0"
    "osd2Position\0OSDFormat_Text\0OSDFormat_Date\0"
    "OSDFormat_Time\0OSDFormat_DateTime\0"
    "OSDFormat_Image\0OSDPosition_Left_Top\0"
    "OSDPosition_Left_Bottom\0OSDPosition_Right_Top\0"
    "OSDPosition_Right_Bottom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      75,   14, // methods
      27,  620, // properties
       2,  701, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  389,    2, 0x06 /* Public */,
       3,    0,  390,    2, 0x06 /* Public */,
       4,    0,  391,    2, 0x06 /* Public */,
       5,    1,  392,    2, 0x06 /* Public */,
       7,    1,  395,    2, 0x06 /* Public */,
       9,    1,  398,    2, 0x06 /* Public */,
      11,    1,  401,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,  404,    2, 0x0a /* Public */,
      15,    0,  407,    2, 0x0a /* Public */,
       9,    0,  408,    2, 0x0a /* Public */,
      16,    0,  409,    2, 0x0a /* Public */,
      17,    0,  410,    2, 0x0a /* Public */,
      18,    1,  411,    2, 0x0a /* Public */,
      20,    0,  414,    2, 0x0a /* Public */,
      21,    1,  415,    2, 0x0a /* Public */,
      23,    0,  418,    2, 0x0a /* Public */,
      24,    1,  419,    2, 0x0a /* Public */,
      26,    1,  422,    2, 0x0a /* Public */,
      28,    1,  425,    2, 0x0a /* Public */,
      30,    1,  428,    2, 0x0a /* Public */,
      32,    1,  431,    2, 0x0a /* Public */,
      34,    1,  434,    2, 0x0a /* Public */,
      35,    1,  437,    2, 0x0a /* Public */,
      37,    1,  440,    2, 0x0a /* Public */,
      39,    1,  443,    2, 0x0a /* Public */,
      41,    1,  446,    2, 0x0a /* Public */,
      43,    1,  449,    2, 0x0a /* Public */,
      45,    1,  452,    2, 0x0a /* Public */,
      47,    1,  455,    2, 0x0a /* Public */,
      49,    1,  458,    2, 0x0a /* Public */,
      51,    1,  461,    2, 0x0a /* Public */,
      53,    1,  464,    2, 0x0a /* Public */,
      55,    1,  467,    2, 0x0a /* Public */,
      57,    1,  470,    2, 0x0a /* Public */,
      59,    1,  473,    2, 0x0a /* Public */,
      61,    1,  476,    2, 0x0a /* Public */,
      63,    1,  479,    2, 0x0a /* Public */,
      65,    1,  482,    2, 0x0a /* Public */,
      67,    1,  485,    2, 0x0a /* Public */,
      69,    1,  488,    2, 0x0a /* Public */,
      71,    1,  491,    2, 0x0a /* Public */,
      73,    1,  494,    2, 0x0a /* Public */,
      75,    1,  497,    2, 0x0a /* Public */,
      77,    1,  500,    2, 0x0a /* Public */,
      79,    1,  503,    2, 0x0a /* Public */,
      81,    1,  506,    2, 0x0a /* Public */,
      84,    1,  509,    2, 0x0a /* Public */,
      87,    1,  512,    2, 0x0a /* Public */,
      88,    1,  515,    2, 0x0a /* Public */,
      89,    1,  518,    2, 0x0a /* Public */,
      90,    1,  521,    2, 0x0a /* Public */,
      91,    1,  524,    2, 0x0a /* Public */,
      92,    1,  527,    2, 0x0a /* Public */,
      93,    1,  530,    2, 0x0a /* Public */,
      94,    0,  533,    2, 0x0a /* Public */,
      95,    1,  534,    2, 0x0a /* Public */,
      97,    0,  537,    2, 0x0a /* Public */,
      98,    0,  538,    2, 0x0a /* Public */,
      99,    1,  539,    2, 0x0a /* Public */,
     101,    1,  542,    2, 0x0a /* Public */,
     102,    4,  545,    2, 0x0a /* Public */,
     109,    1,  554,    2, 0x0a /* Public */,
     110,    1,  557,    2, 0x0a /* Public */,
     111,    4,  560,    2, 0x0a /* Public */,
     117,    6,  569,    2, 0x0a /* Public */,
     123,    6,  582,    2, 0x0a /* Public */,
     125,    3,  595,    2, 0x0a /* Public */,
     128,    0,  602,    2, 0x0a /* Public */,
     129,    0,  603,    2, 0x0a /* Public */,
     130,    0,  604,    2, 0x0a /* Public */,
     131,    0,  605,    2, 0x0a /* Public */,
     132,    0,  606,    2, 0x0a /* Public */,
     133,    0,  607,    2, 0x0a /* Public */,
     134,    4,  608,    2, 0x0a /* Public */,
     139,    1,  617,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Void, QMetaType::QString,   42,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void, QMetaType::Bool,   46,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Bool,   50,
    QMetaType::Void, QMetaType::Bool,   52,
    QMetaType::Void, QMetaType::Bool,   54,
    QMetaType::Void, QMetaType::QColor,   56,
    QMetaType::Void, QMetaType::QColor,   58,
    QMetaType::Void, QMetaType::Int,   60,
    QMetaType::Void, QMetaType::Int,   62,
    QMetaType::Void, QMetaType::QColor,   64,
    QMetaType::Void, QMetaType::QColor,   66,
    QMetaType::Void, QMetaType::QString,   68,
    QMetaType::Void, QMetaType::QImage,   70,
    QMetaType::Void, QMetaType::Bool,   72,
    QMetaType::Void, QMetaType::Int,   74,
    QMetaType::Void, QMetaType::QString,   76,
    QMetaType::Void, QMetaType::QColor,   78,
    QMetaType::Void, QMetaType::QImage,   80,
    QMetaType::Void, 0x80000000 | 82,   83,
    QMetaType::Void, 0x80000000 | 85,   86,
    QMetaType::Void, QMetaType::Bool,   72,
    QMetaType::Void, QMetaType::Int,   74,
    QMetaType::Void, QMetaType::QString,   76,
    QMetaType::Void, QMetaType::QColor,   78,
    QMetaType::Void, QMetaType::QImage,   80,
    QMetaType::Void, 0x80000000 | 82,   83,
    QMetaType::Void, 0x80000000 | 85,   86,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 96,   13,
    0x80000000 | 96,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::VoidStar,  100,
    QMetaType::Void, QMetaType::VoidStar,   13,
    QMetaType::Void, 0x80000000 | 103, QMetaType::Int, QMetaType::Int, 0x80000000 | 107,  104,  105,  106,  108,
    QMetaType::Bool, QMetaType::VoidStar,  100,
    QMetaType::Void, QMetaType::VoidStar,   13,
    QMetaType::Bool, 0x80000000 | 112, 0x80000000 | 112, QMetaType::Int, QMetaType::Int,  113,  114,  115,  116,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 112, 0x80000000 | 112, 0x80000000 | 121, QMetaType::Int, QMetaType::Int,  118,  119,  120,  122,  115,  116,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 112, 0x80000000 | 112, 0x80000000 | 112, QMetaType::Int, QMetaType::Int,  118,  119,  120,  124,  115,  116,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 127, 0x80000000 | 127,  126,  115,  116,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 135, 0x80000000 | 137, QMetaType::Int, QMetaType::Int,  136,  138,  115,  116,
    QMetaType::Bool, QMetaType::VoidStar,  100,

 // properties: name, type, flags
      46, QMetaType::Bool, 0x00095103,
      48, QMetaType::Bool, 0x00095103,
      50, QMetaType::Bool, 0x00095103,
      52, QMetaType::Bool, 0x00095103,
      54, QMetaType::Bool, 0x00095103,
      56, QMetaType::QColor, 0x00095103,
      58, QMetaType::QColor, 0x00095103,
      60, QMetaType::Int, 0x00095103,
      62, QMetaType::Int, 0x00095103,
      64, QMetaType::QColor, 0x00095103,
      66, QMetaType::QColor, 0x00095103,
      68, QMetaType::QString, 0x00095103,
      70, QMetaType::QImage, 0x00095103,
     140, QMetaType::Bool, 0x00095003,
     141, QMetaType::Int, 0x00095003,
     142, QMetaType::QString, 0x00095003,
     143, QMetaType::QColor, 0x00095003,
     144, QMetaType::QImage, 0x00095003,
     145, 0x80000000 | 82, 0x0009500b,
     146, 0x80000000 | 85, 0x0009500b,
     147, QMetaType::Bool, 0x00095003,
     148, QMetaType::Int, 0x00095003,
     149, QMetaType::QString, 0x00095003,
     150, QMetaType::QColor, 0x00095003,
     151, QMetaType::QImage, 0x00095003,
     152, 0x80000000 | 82, 0x0009500b,
     153, 0x80000000 | 85, 0x0009500b,

 // enums: name, flags, count, data
      82, 0x0,    5,  709,
      85, 0x0,    4,  719,

 // enum data: key, value
     154, uint(VideoWidget::OSDFormat_Text),
     155, uint(VideoWidget::OSDFormat_Date),
     156, uint(VideoWidget::OSDFormat_Time),
     157, uint(VideoWidget::OSDFormat_DateTime),
     158, uint(VideoWidget::OSDFormat_Image),
     159, uint(VideoWidget::OSDPosition_Left_Top),
     160, uint(VideoWidget::OSDPosition_Left_Bottom),
     161, uint(VideoWidget::OSDPosition_Right_Top),
     162, uint(VideoWidget::OSDPosition_Right_Bottom),

       0        // eod
};

void VideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoWidget *_t = static_cast<VideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receivePlayStart(); break;
        case 1: _t->receivePlayError(); break;
        case 2: _t->receivePlayFinsh(); break;
        case 3: _t->receiveImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 4: _t->fileDrag((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->btnClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->pushVideoh264Data((*reinterpret_cast< const MP_DATA_INFO(*)>(_a[1]))); break;
        case 7: _t->updateImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 8: _t->checkVideo(); break;
        case 9: _t->btnClicked(); break;
        case 10: { uint _r = _t->getLength();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 11: { uint _r = _t->getPosition();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: { bool _r = _t->getMute();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->setMute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: { int _r = _t->getVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->setInterval((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->setSleepTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->setCheckTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->setCheckConn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setUrl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->setHardware((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->setSaveFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->setSaveInterval((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->setSavePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->setFileName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: _t->setCopyImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->setCheckLive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->setDrawImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->setFillImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->setFlowEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->setFlowBgColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 33: _t->setFlowPressColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 34: _t->setTimeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->setBorderWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->setBorderColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 37: _t->setFocusColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 38: _t->setBgText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 39: _t->setBgImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 40: _t->setOSD1Visible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: _t->setOSD1FontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->setOSD1Text((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 43: _t->setOSD1Color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 44: _t->setOSD1Image((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 45: _t->setOSD1Format((*reinterpret_cast< const OSDFormat(*)>(_a[1]))); break;
        case 46: _t->setOSD1Position((*reinterpret_cast< const OSDPosition(*)>(_a[1]))); break;
        case 47: _t->setOSD2Visible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->setOSD2FontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->setOSD2Text((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 50: _t->setOSD2Color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 51: _t->setOSD2Image((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 52: _t->setOSD2Format((*reinterpret_cast< const OSDFormat(*)>(_a[1]))); break;
        case 53: _t->setOSD2Position((*reinterpret_cast< const OSDPosition(*)>(_a[1]))); break;
        case 54: { int _r = _t->getHStreamCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 55: _t->pushHStreamInfo((*reinterpret_cast< MP_DATA_INFO*(*)>(_a[1]))); break;
        case 56: { MP_DATA_INFO* _r = _t->getHStreamInfo();
            if (_a[0]) *reinterpret_cast< MP_DATA_INFO**>(_a[0]) = std::move(_r); }  break;
        case 57: _t->startVideoThread(); break;
        case 58: { bool _r = _t->ish265IFrame((*reinterpret_cast< void*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->setVideoh264Data((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 60: _t->RGB2Image((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QImage*(*)>(_a[4]))); break;
        case 61: { bool _r = _t->isIFrame((*reinterpret_cast< void*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 62: _t->setVideoYUVData((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 63: { bool _r = _t->YV12ToBGR24_FFmpeg((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 64: _t->Yuv420p2Rgb32((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< unsigned char*(*)>(_a[3])),(*reinterpret_cast< const BYTE*(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 65: _t->YUV420_2_RGB((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< unsigned char*(*)>(_a[3])),(*reinterpret_cast< unsigned char*(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 66: _t->getVideoResolution((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 67: _t->open(); break;
        case 68: _t->pause(); break;
        case 69: _t->next(); break;
        case 70: _t->close(); break;
        case 71: _t->restart(); break;
        case 72: _t->clear(); break;
        case 73: { bool _r = _t->vtInit((*reinterpret_cast< AVCodecID(*)>(_a[1])),(*reinterpret_cast< IVideoCall*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 74: { bool _r = _t->initPacket((*reinterpret_cast< void*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::receivePlayStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::receivePlayError)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::receivePlayFinsh)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::receiveImage)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::fileDrag)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::btnClicked)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(const MP_DATA_INFO & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::pushVideoh264Data)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        VideoWidget *_t = static_cast<VideoWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->getCopyImage(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->getCheckLive(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->getDrawImage(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->getFillImage(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->getFlowEnable(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->getFlowBgColor(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->getFlowPressColor(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->getTimeout(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->getBorderWidth(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->getBorderColor(); break;
        case 10: *reinterpret_cast< QColor*>(_v) = _t->getFocusColor(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->getBgText(); break;
        case 12: *reinterpret_cast< QImage*>(_v) = _t->getBgImage(); break;
        case 13: *reinterpret_cast< bool*>(_v) = _t->getOSD1Visible(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->getOSD1FontSize(); break;
        case 15: *reinterpret_cast< QString*>(_v) = _t->getOSD1Text(); break;
        case 16: *reinterpret_cast< QColor*>(_v) = _t->getOSD1Color(); break;
        case 17: *reinterpret_cast< QImage*>(_v) = _t->getOSD1Image(); break;
        case 18: *reinterpret_cast< OSDFormat*>(_v) = _t->getOSD1Format(); break;
        case 19: *reinterpret_cast< OSDPosition*>(_v) = _t->getOSD1Position(); break;
        case 20: *reinterpret_cast< bool*>(_v) = _t->getOSD2Visible(); break;
        case 21: *reinterpret_cast< int*>(_v) = _t->getOSD2FontSize(); break;
        case 22: *reinterpret_cast< QString*>(_v) = _t->getOSD2Text(); break;
        case 23: *reinterpret_cast< QColor*>(_v) = _t->getOSD2Color(); break;
        case 24: *reinterpret_cast< QImage*>(_v) = _t->getOSD2Image(); break;
        case 25: *reinterpret_cast< OSDFormat*>(_v) = _t->getOSD2Format(); break;
        case 26: *reinterpret_cast< OSDPosition*>(_v) = _t->getOSD2Position(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        VideoWidget *_t = static_cast<VideoWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCopyImage(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setCheckLive(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setDrawImage(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setFillImage(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setFlowEnable(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setFlowBgColor(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setFlowPressColor(*reinterpret_cast< QColor*>(_v)); break;
        case 7: _t->setTimeout(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->setBorderWidth(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        case 10: _t->setFocusColor(*reinterpret_cast< QColor*>(_v)); break;
        case 11: _t->setBgText(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->setBgImage(*reinterpret_cast< QImage*>(_v)); break;
        case 13: _t->setOSD1Visible(*reinterpret_cast< bool*>(_v)); break;
        case 14: _t->setOSD1FontSize(*reinterpret_cast< int*>(_v)); break;
        case 15: _t->setOSD1Text(*reinterpret_cast< QString*>(_v)); break;
        case 16: _t->setOSD1Color(*reinterpret_cast< QColor*>(_v)); break;
        case 17: _t->setOSD1Image(*reinterpret_cast< QImage*>(_v)); break;
        case 18: _t->setOSD1Format(*reinterpret_cast< OSDFormat*>(_v)); break;
        case 19: _t->setOSD1Position(*reinterpret_cast< OSDPosition*>(_v)); break;
        case 20: _t->setOSD2Visible(*reinterpret_cast< bool*>(_v)); break;
        case 21: _t->setOSD2FontSize(*reinterpret_cast< int*>(_v)); break;
        case 22: _t->setOSD2Text(*reinterpret_cast< QString*>(_v)); break;
        case 23: _t->setOSD2Color(*reinterpret_cast< QColor*>(_v)); break;
        case 24: _t->setOSD2Image(*reinterpret_cast< QImage*>(_v)); break;
        case 25: _t->setOSD2Format(*reinterpret_cast< OSDFormat*>(_v)); break;
        case 26: _t->setOSD2Position(*reinterpret_cast< OSDPosition*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject VideoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoWidget.data,
      qt_meta_data_VideoWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoWidget.stringdata0))
        return static_cast<void*>(const_cast< VideoWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 75)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 75;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 75)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 75;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 27;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 27;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 27;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 27;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 27;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VideoWidget::receivePlayStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VideoWidget::receivePlayError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VideoWidget::receivePlayFinsh()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VideoWidget::receiveImage(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VideoWidget::fileDrag(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VideoWidget::btnClicked(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VideoWidget::pushVideoh264Data(const MP_DATA_INFO & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
