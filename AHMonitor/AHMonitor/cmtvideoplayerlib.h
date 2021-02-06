/****************************************************************************
**
** Namespace CmtVideoPlayerLib generated by dumpcpp v5.9.0 using
** dumpcpp.exe {0F12902B-28AB-4127-8070-931503B8EBA3}
** from the type library C:\Windows\SysWow64\CmtVideoPlayer.ocx
**
****************************************************************************/

#ifndef QAX_DUMPCPP_CMTVIDEOPLAYERLIB_H
#define QAX_DUMPCPP_CMTVIDEOPLAYERLIB_H

// Define this symbol to __declspec(dllexport) or __declspec(dllimport)
#ifndef CMTVIDEOPLAYERLIB_EXPORT
#define CMTVIDEOPLAYERLIB_EXPORT
#endif

#include <qaxobject.h>
#include <qaxwidget.h>
#include <qdatetime.h>
#include <qpixmap.h>

struct IDispatch;


// Referenced namespace

namespace CmtVideoPlayerLib {


class CMTVIDEOPLAYERLIB_EXPORT _DCmtVideoPlayer : public QAxObject
{
public:
    _DCmtVideoPlayer(IDispatch *subobject = 0, QAxObject *parent = 0)
    : QAxObject((IUnknown*)subobject, parent)
    {
        internalRelease();
    }

    /*
    Method GetHWnd
    */
    inline int GetHWnd();

    /*
    Method setVpIndex
    */
    inline void setVpIndex(int index);

// meta object functions
    static const QMetaObject staticMetaObject;
    virtual const QMetaObject *metaObject() const { return &staticMetaObject; }
    virtual void *qt_metacast(const char *);
};

// skipping event interface _DCmtVideoPlayerEvents

// Actual coclasses
class CMTVIDEOPLAYERLIB_EXPORT CmtVideoPlayer : public QAxWidget
{
public:
    CmtVideoPlayer(QWidget *parent = 0, Qt::WindowFlags f = 0)
    : QAxWidget(parent, f)
    {
        setControl("{790b714b-552a-4c40-aa78-4fc72c8f7af8}");
    }

    CmtVideoPlayer(_DCmtVideoPlayer *iface)
    : QAxWidget()
    {
        initializeFrom(iface);
        delete iface;
    }

    /*
    Method GetHWnd
    */
    inline int GetHWnd();

    /*
    Method setVpIndex
    */
    inline void setVpIndex(int index);

// meta object functions
    static const QMetaObject staticMetaObject;
    virtual const QMetaObject *metaObject() const { return &staticMetaObject; }
    virtual void *qt_metacast(const char *);
};

// member function implementation
#ifndef QAX_DUMPCPP_CMTVIDEOPLAYERLIB_NOINLINES
inline int _DCmtVideoPlayer::GetHWnd()
{
    int qax_result;
    void *_a[] = {(void*)&qax_result};
    qt_metacall(QMetaObject::InvokeMetaMethod, 8, _a);
    return qax_result;
}

inline void _DCmtVideoPlayer::setVpIndex(int index)
{
    void *_a[] = {0, (void*)&index};
    qt_metacall(QMetaObject::InvokeMetaMethod, 9, _a);
}


inline int CmtVideoPlayer::GetHWnd()
{
    int qax_result;
    void *_a[] = {(void*)&qax_result};
    qt_metacall(QMetaObject::InvokeMetaMethod, 36, _a);
    return qax_result;
}

inline void CmtVideoPlayer::setVpIndex(int index)
{
    void *_a[] = {0, (void*)&index};
    qt_metacall(QMetaObject::InvokeMetaMethod, 37, _a);
}



#endif

}

QT_BEGIN_NAMESPACE

namespace QtMetaTypePrivate {
template<>
struct QMetaTypeFunctionHelper<CmtVideoPlayerLib::_DCmtVideoPlayer, /* Accepted */ true> {
    static void Destruct(void *t)
    {
        Q_UNUSED(t)
        static_cast<CmtVideoPlayerLib::_DCmtVideoPlayer*>(t)->CmtVideoPlayerLib::_DCmtVideoPlayer::~_DCmtVideoPlayer();
    }
    static void *Construct(void *where, const void *t)
    {
        Q_ASSERT(!t);
        Q_UNUSED(t)
        return new (where) CmtVideoPlayerLib::_DCmtVideoPlayer;
    }
#ifndef QT_NO_DATASTREAM
    static void Save(QDataStream &stream, const void *t) { stream << *static_cast<const CmtVideoPlayerLib::_DCmtVideoPlayer*>(t); }
    static void Load(QDataStream &stream, void *t) { stream >> *static_cast<CmtVideoPlayerLib::_DCmtVideoPlayer*>(t); }
#endif // QT_NO_DATASTREAM
};

template<>
struct QMetaTypeFunctionHelper<CmtVideoPlayerLib::CmtVideoPlayer, /* Accepted */ true> {
    static void Destruct(void *t)
    {
        Q_UNUSED(t)
        static_cast<CmtVideoPlayerLib::CmtVideoPlayer*>(t)->CmtVideoPlayerLib::CmtVideoPlayer::~CmtVideoPlayer();
    }
    static void *Construct(void *where, const void *t)
    {
        Q_ASSERT(!t);
        Q_UNUSED(t)
        return new (where) CmtVideoPlayerLib::CmtVideoPlayer;
    }
#ifndef QT_NO_DATASTREAM
    static void Save(QDataStream &stream, const void *t) { stream << *static_cast<const CmtVideoPlayerLib::CmtVideoPlayer*>(t); }
    static void Load(QDataStream &stream, void *t) { stream >> *static_cast<CmtVideoPlayerLib::CmtVideoPlayer*>(t); }
#endif // QT_NO_DATASTREAM
};

} // namespace QtMetaTypePrivate
QT_END_NAMESPACE

#endif
