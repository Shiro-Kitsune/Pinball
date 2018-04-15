#include "stdafx.h"
#include "Background.h"

Background::Background(const CTable & table) : m_table(table)
{
}

CTable & Background::GetTable()
{
	return m_table;
}
