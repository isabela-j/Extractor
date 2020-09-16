#pragma once
#include "AbstractVRDialog.h"

class UIDialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit UIDialog(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~UIDialog()=default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;
private:
	void presets(const QString& t_description) override;
};

