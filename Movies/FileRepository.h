#pragma once
#include "Repository.h"

class FileRepository :
    public Repository
{
public:
    FileRepository(const std::string& path, bool initialize = false);

    void AddElement(const Movie& newMovie) override;
    void RemoveElemnt(size_t position) override;

    void UpdateTitle(size_t position, std::string newName) override;
    void UpdateGenre(size_t position, std::string newGenre) override;
    void UpdateYear(size_t position, size_t newYear) override;
    void UpdateLikes(size_t position, size_t newLikes) override;
    void UpdateTrailer(size_t position, std::string newTrailer) override;

    bool IsInitializable() const;
protected:
    std::string filePath;
    bool initialize;
private:
    void ReadData();
    void WriteData();
};
