#pragma once

#include "Component.h"
#include "table.h"

class Background : public Component
{
public:
	Background(const CTable& table);
	CTable& GetTable();
private:
	CTable m_table;
};