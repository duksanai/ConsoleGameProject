#include "Joker.h"

Joker::Joker(const std::string& name, const std::string& toolTip)
	:name(name), toolTip(toolTip)
{
}

std::string Joker::getName()
{
	return name;
}

std::string Joker::getToolTip()
{
	return toolTip;
}
