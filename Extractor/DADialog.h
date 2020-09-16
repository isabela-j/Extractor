#pragma once
#include "AbstractVRDialog.h"
class DADialog: public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit DADialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~DADialog()=default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
	
};

