#pragma once
#include "AbstractVRDialog.h"
class DSDialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit DSDialog(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~DSDialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

