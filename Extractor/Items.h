#pragma once

#include <QTreeWidget>


class Items final : public QTreeWidgetItem
{
public:
	Items() = default;
	Items(const QString& tagID, const QString& VR,
		const QString& VM, const QString& length,
		const QString& desc, const QString& value, const int& level);
	~Items() = default;

	enum class type
	{
		id,
		vr,
		vm,
		length,
		desc,
		val
	};

	[[nodiscard]] int getLevel() const { return m_level; }
	[[nodiscard]] QString getTagId() const { return text(0); }
	[[nodiscard]] QString getValue() const { return text(5); }
	[[nodiscard]] QString getLength() const { return text(3); }
	[[nodiscard]] QString getVR() const { return text(1); }
private:
	int m_level = 0;
};
