#pragma once
#include "AbstractVRDialog.h"

class USInsertEdit final : public AbstractVRDialog
{
	Q_OBJECT
public:
	USInsertEdit(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~USInsertEdit() = default;
	void setLineEditValue(const QString& t_value) const { m_ui.lineEditValue->setText(t_value); }
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

