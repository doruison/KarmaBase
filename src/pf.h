#ifndef PF_H
#define PF_H

#define ALL_PAGES 0
typedef int RC;
typedef int PageNum;


class PF_PageHandle {
public:
	PF_PageHandle();                          // Default constructor
	~PF_PageHandle();                          // Destructor
	PF_PageHandle(const PF_PageHandle &pageHandle);
	// Copy constructor
	PF_PageHandle& operator= (const PF_PageHandle &pageHandle);
	// Overload =
	RC GetData(char *&pData) const;        // Set pData to point to
	//   the page contents
	RC GetPageNum(PageNum &pageNum) const;    // Return the page number
};

class PF_FileHandle {
public:
	PF_FileHandle();                                  // Default constructor
	~PF_FileHandle();                                  // Destructor
	PF_FileHandle(const PF_FileHandle &fileHandle);   // Copy constructor
	PF_FileHandle& operator= (const PF_FileHandle &fileHandle);
	// Overload =
	RC GetFirstPage(PF_PageHandle &pageHandle) const;   // Get the first page
	RC GetLastPage(PF_PageHandle &pageHandle) const;   // Get the last page

	RC GetNextPage(PageNum current, PF_PageHandle &pageHandle) const;
	// Get the next page
	RC GetPrevPage(PageNum current, PF_PageHandle &pageHandle) const;
	// Get the previous page
	RC GetThisPage(PageNum pageNum, PF_PageHandle &pageHandle) const;
	// Get a specific page
	RC AllocatePage(PF_PageHandle &pageHandle);         // Allocate a new page
	RC DisposePage(PageNum pageNum);                   // Dispose of a page 
	RC MarkDirty(PageNum pageNum) const;             // Mark a page as dirty
	RC UnpinPage(PageNum pageNum) const;             // Unpin a page
	RC ForcePages(PageNum pageNum = ALL_PAGES) const; // Write dirty page(s)
	//   to disk
};



class PF_Manager
{
public:
	PF_Manager();                           // Constructor
	~PF_Manager();                           // Destructor
	RC CreateFile(const char *fileName);       // Create a new file
	RC DestroyFile(const char *fileName);       // Destroy a file
	RC OpenFile(const char *fileName, PF_FileHandle &fileHandle);
	// Open a file
	RC CloseFile(PF_FileHandle &fileHandle);  // Close a file
	RC AllocateBlock(char *&buffer);              // Allocate a new scratch page in buffer
	RC DisposeBlock(char *buffer);               // Dispose of a scratch page
};






#endif