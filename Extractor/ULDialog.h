#pragma once
#include "AbstractVRDialog.h"
class ULDialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit ULDialog(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~ULDialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

