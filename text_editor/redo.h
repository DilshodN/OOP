#pragma once

#include "service_command.h"


class RedoCommand final : public ServiceCommand{
public:
    void execute(Editor& editor) const override;
};