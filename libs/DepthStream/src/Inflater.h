#pragma once

#include <memory>

namespace depth {
  class Inflater;
  typedef std::shared_ptr<Inflater> InflaterRef;

  class Inflater {
    public:
      ~Inflater(){
        destroy();
      }

      void destroy();

      bool inflate(const void* data, size_t size);
      size_t getSize() const { return inflateSize; }
      const void* getData() const { return (void*)decompressed; }
      void* releaseData(){ void* tmp = (void*)decompressed; decompressed=NULL; return tmp; }
      size_t getFailCount() const { return failCount; }

    protected:

      void growTo(size_t to);
      const void* decompress(const void* compressedBytes, unsigned int length);

      std::ostream& cout() { return std::cout << "[depth::Inflater] "; }
      std::ostream& cerr() { return std::cerr << "[depth::Inflater] "; }

    private:
      char* decompressed=NULL;
      size_t currentBufferSize=0;
      size_t inflateSize=0;
      size_t failCount=0;
      bool bVerbose=false;
  };
}