#include "Items.h"

Items::Items(const QString& tagID, const QString& VR,
             const QString& VM, const QString& length,
             const QString& desc, const QString& value, const int& level) : m_level(level)
{
	setText(static_cast<int>(type::id), tagID);
	setText(static_cast<int>(type::vr), VR);
	setText(static_cast<int>(type::vm), VM);
	setText(static_cast<int>(type::length), length);
	setText(static_cast<int>(type::desc), desc);
	setText(static_cast<int>(type::val), value);
	QTreeWidgetItem::setData(0, 1, level);
}
