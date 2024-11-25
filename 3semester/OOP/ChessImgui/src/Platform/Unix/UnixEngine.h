#pragma once

#include "Engine/Engine.h"

#include <unistd.h>

#include <filesystem>

class UnixEngine : public Engine {
public:
    UnixEngine(const std::filesystem::path& path);

    ~UnixEngine() override;

    void Send(const std::string& message) override;
    bool Receive(std::string& message) override;
private:
                   int m_InputFilePipes[2];
    int m_OutputFilePipes[2];

         pid_t m_EnginePID;
};
