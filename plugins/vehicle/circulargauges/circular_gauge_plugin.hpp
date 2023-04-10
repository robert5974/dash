// circular_gauge_plugin.hpp

#pragma once

#include <QObject>
#include <QtPlugin>
#include <canbus/ICANBus.hpp>
#include <QVBoxLayout>
#include <QLabel>

class CircularGauge : public QWidget {
    Q_OBJECT
public:
    CircularGauge(QWidget* parent = nullptr);

public slots:
    void updateValue(QByteArray data);

private:
    QLabel* m_valueLabel;
};

class CircularGaugePlugin : public QObject, public ICANBusPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VehiclePlugin_iid FILE "circulargauges.json")
    Q_INTERFACES(ICANBusPlugin)

public:
    CircularGaugePlugin();
    bool init(ICANBus* canBus) override;

private:
    ICANBus* m_canBus;
    QVBoxLayout* m_layout;
    CircularGauge* m_gauge;
};

