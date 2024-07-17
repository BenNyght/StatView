
#include "FileUtility.h"
#include "tinyfiledialogs.h"

std::string FileUtility::OpenFilePanel(const std::string& title, const std::string& path, std::vector<std::string> extensions)
{
    std::string fileTypesDescription {};
	std::vector<const char*> filterPatterns;
    filterPatterns.reserve(extensions.size());
    for (auto& extension : extensions) 
    {
        extension = "*." + extension;
        filterPatterns.push_back(extension.c_str());
        fileTypesDescription += extension + " ";
    }

    if (const char* selectedFile = tinyfd_openFileDialog(
	    title.c_str(),                      // Dialog title
	    path.c_str(),                       // Default path
	    static_cast<int>(extensions.size()),// Number of filter patterns
	    filterPatterns.data(),              // Filter patterns
	    fileTypesDescription.c_str(),       // Description of file types
	    0                                   // Allow multiple selection
    ))
    {
	    return selectedFile;
    }

    return std::string {};
}
