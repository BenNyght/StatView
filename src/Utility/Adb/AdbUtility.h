#pragma once
#include <string>

class AdbUtility
{
public:
	static void RunCommandOnThread(const std::string& command);
	static void RunCommand(const std::string& command);
	static std::string RunCommandToFile(const std::string& command);
	static void SetBufferSize(const int sizeInMb);

	static void StartAdb();
	static void RestartAdb();
	static void KillAdb();

private:
	static std::string ReadAndCleanupTempFile(const std::string& tempFileName);
};
