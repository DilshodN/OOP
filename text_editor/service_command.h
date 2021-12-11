#pragma once
#include "editor.h"
class ServiceCommand
{
public:
    virtual void execute(Editor& editor) const = 0;
    virtual ~ServiceCommand() = default;
};
