#pragma once

#include <QCameraDevice>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QList>
#include <QMediaDevices>
#include <QMediaPlayer>
#include <QPair>
#include <QRadioButton>
#include <QStackedLayout>
#include <QString>
#include <QVideoWidget>
#include <QWidget>

#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Bus>
#include <QGst/ElementFactory>
#include <QGst/Init>
#include <QGst/Message>
#include <QGst/Parse>
#include <QGst/Pipeline>
#include <QGst/Quick/VideoSurface>
#include <QGst/Ui/VideoWidget>
#include <QGst/Utils/ApplicationSink>
#include <QGst/Utils/ApplicationSource>
#include <QtQml/QQmlContext>
#include <QtQuickWidgets/QQuickWidget>
#include <gst/app/gstappsink.h>
#include <gst/app/gstappsrc.h>
#include <gst/gst.h>
#include <gst/video/video.h>

#include "DashLog.hpp"
#include "app/config.hpp"

#include "app/pages/page.hpp"

class Arbiter;

class CameraPage : public QWidget, public Page {
  Q_OBJECT

public:
  CameraPage(Arbiter &arbiter, QWidget *parent = nullptr);

  void init() override;

private:
  class VideoContainer : public QWidget {
  public:
    VideoContainer(QWidget *parent = nullptr, CameraPage *page = nullptr);

  private:
    void resizeEvent(QResizeEvent *event);

    CameraPage *page;
  };

  class Settings : public QWidget {
  public:
    Settings(Arbiter &arbiter, QWidget *parent = nullptr);
    QSize sizeHint() const override;

  private:
    QWidget *settings_widget();
    QWidget *camera_overlay_row_widget();
    QWidget *camera_overlay_width_row_widget();
    QWidget *camera_overlay_height_row_widget();
    QWidget *camera_overlay_width_widget();
    QWidget *camera_overlay_height_widget();

    Arbiter &arbiter;
    Config *config;
  };

  QWidget *connect_widget();
  QWidget *network_camera_widget();
  QWidget *local_camera_widget();
  QWidget *local_cam_selector();
  QPushButton *connect_button();
  QWidget *network_cam_selector();
  QWidget *selector_widget(QWidget *selection);
  void populate_local_cams();
  void connect_network_stream();
  void connect_local_stream();
  bool local_cam_available(const QString &device);
  QSize choose_video_resolution();
  void count_down();
  void connect_cam();
  void init_gstreamer_pipeline(std::string vidLaunchStr_, bool sync = false);
  void disconnect_stream();

  static GstPadProbeReturn convertProbe(GstPad *pad, GstPadProbeInfo *info,
                                        void *);
  static gboolean busCallback(GstBus *, GstMessage *message, gpointer *);
  void showEvent(QShowEvent *event);

  QGst::ElementPtr videoSink_;
  QQuickWidget *videoWidget_;
  GstElement *vidPipeline_;
  GstAppSrc *vidSrc_;
  QWidget *videoContainer_;
  QGst::Quick::VideoSurface *surface_;

  QMediaPlayer *player;
  int local_index;
  QTimer *reconnect_timer;
  Config *config;
  bool connected;
  QLabel *status;
  VideoContainer *local_video_widget;
  VideoContainer *remote_video_widget;
  int reconnect_in_secs;
  QString reconnect_message;
  QList<QPair<QString, QString>> local_cams;

signals:
  void connected_network();
  void connected_local();
  void disconnected();
  void autoconnect_disabled();
  void next_cam();
  void prev_cam();
};
