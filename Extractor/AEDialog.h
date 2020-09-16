#pragma once
#pragma once
#include "AbstractVRDialog.h"
class AEDialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit AEDialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~AEDialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};


