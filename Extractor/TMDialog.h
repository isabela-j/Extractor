#pragma once
#include "AbstractVRDialog.h"
class TMDialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit TMDialog(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~TMDialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

