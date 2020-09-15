#pragma once
#include "AbstractVRDialog.h"
class LODialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit LODialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~LODialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
	
};

