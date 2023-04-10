// circular_gauge_plugin.cpp

#include "circular_gauge_plugin.hpp"

CircularGauge::CircularGauge(QWidget* parent)
    : QWidget(parent)
{
    // Set up the layout for the gauge
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_valueLabel = new QLabel("0", this);
    layout->addWidget(m_valueLabel);

    // Set up the default appearance of the gauge
    setMinimumSize(100, 100);
    setStyleSheet("background-color: black; border: 1px solid white; border-radius: 50%;");
}

void CircularGauge::updateValue(QByteArray data)
{
    // Convert the received data to a double value
    double value = 0;
    if (data.size() == 4) {
        uint32_t intValue = 0;
        memcpy(&intValue, data.constData(), 4);
        value = static_cast<double>(intValue);
    } else {
        return;
    }

    // Update the value displayed on the gauge
    m_valueLabel->setText(QString::number(value));
}

CircularGaugePlugin::CircularGaugePlugin()
    : m_canBus(nullptr)
    , m_layout(nullptr)
    , m_gauge(nullptr)
{
}

bool CircularGaugePlugin::init(ICANBus* canBus)
{
    m_canBus = canBus;

    // Set up the gauge widget and layout
    m_gauge = new CircularGauge();
    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_gauge);
    setLayout(m_layout);

    // Register a callback to update the gauge whenever a CANBus message with ID 10 is received
    m_canBus->registerFrameHandler(10, [this](QByteArray data) {
        m_gauge->updateValue(data);
    });

    return true;
}

// Export the plugin to the Qt plugin system
Q_EXPORT_PLUGIN2(circular_gauge_plugin, CircularGaugePlugin)

