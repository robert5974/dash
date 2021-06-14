#pragma once

#include <QFrame>

#include "app/quick_views/quick_view.hpp"

class Arbiter;

class EqualizerQuickView : public QFrame, public QuickView {
    Q_OBJECT

   public:
    EqualizerQuickView(Arbiter &arbiter);

    void init() override;
};
