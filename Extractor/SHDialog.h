#pragma once
#include "AbstractVRDialog.h"
class SHDialog final: public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit SHDialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~SHDialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

