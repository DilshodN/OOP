#pragma once

#include "service_command.h"

class UndoCommand final : public ServiceCommand{
public:
    void execute(Editor& editor) const override;
};