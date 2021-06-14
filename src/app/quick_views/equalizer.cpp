#include <QElapsedTimer>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "app/arbiter.hpp"
#include "app/widgets/dialog.hpp"

#include "app/quick_views/equalizer.hpp"

EqualizerQuickView::EqualizerQuickView(Arbiter &arbiter)
    : QFrame()
    , QuickView(arbiter, "equalizer", this)
{
}
### Define button to open dialog
void EqualizerQuickView::init()
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto equalizer = new QPushButton();
    equalizer->setFlat(true);
    this->arbiter.forge().iconize("equalizer", equalizer, 26);
    auto equalizer_dialog = new Dialog(this->arbiter, false, equalizer);
    equalizer_dialog->set_body(this->arbiter.forge().equalizer_slider(false));
    auto equalizer_timer = new QElapsedTimer();
    connect(equalizer, &QPushButton::pressed, [equalizer_timer]{ equalizer_timer->start(); });
    connect(equalizer, &QPushButton::released, [this, equalizer_timer, equalizer_dialog]{
        if (equalizer_timer->hasExpired(1000))
            this->arbiter.set_equalizer(0);
        else
            equalizer_dialog->open(2000);
	
	});
    auto band1_value = new QLabel(QString::number(this->arbiter.system().band1));
    band1_value->setFont(this->arbiter.forge().font(10));
    connect(&this->arbiter, &Arbiter::band1_changed, [band1_value](uint8_t band1){
        band1_value->setText(QString::number(band1));
    });
	
	});
    auto band2_value = new QLabel(QString::number(this->arbiter.eq().band2));
    band2_value->setFont(this->arbiter.forge().font(10));
    connect(&this->arbiter, &Arbiter::band2_changed, [band2_value](uint8_t band2){
        band2_value->setText(QString::number(band2));
    });
	
    });
    auto preset_value = new QLabel(QString::number(this->arbiter.system().preset));
    preset_value->setFont(this->arbiter.forge().font(10));
    connect(&this->arbiter, &Arbiter::preset_changed, [preset_value](uint8_t preset){
        preset_value->setText(QString::number(preset));
    });

    auto brightness = new QPushButton();
    brightness->setFlat(true);
    this->arbiter.forge().iconize("brightness_high", brightness, 26);
    auto brightness_dialog = new Dialog(this->arbiter, false, brightness);
    brightness_dialog->set_body(this->arbiter.forge().brightness_slider(false));
    connect(brightness, &QPushButton::clicked, [brightness_dialog]{ brightness_dialog->open(2000); });
    auto brightness_value = new QLabel(QString::number(std::ceil(this->arbiter.system().brightness.value / 2.55)));
    brightness_value->setFont(this->arbiter.forge().font(10));
    connect(&this->arbiter, &Arbiter::brightness_changed, [brightness_value](uint8_t brightness){
        brightness_value->setText(QString::number(std::ceil(brightness / 2.55)));
    });

    #auto dark_mode = new QPushButton();
   # dark_mode->setFlat(true);
    #this->arbiter.forge().iconize("dark_mode", dark_mode, 26);
    #connect(dark_mode, &QPushButton::clicked, [this]{ this->arbiter.toggle_mode(); });

    layout->addWidget(equalizer, 1);
    layout->addWidget(equalizer_value, 7);
    #layout->addStretch();
    #layout->addWidget(brightness, 1);
    #layout->addWidget(brightness_value, 7);
    #layout->addStretch();
    #layout->addWidget(dark_mode, 1);
}
