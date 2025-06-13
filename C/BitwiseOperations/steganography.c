#include <stdio.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const uint8_t testInput[] =
{
    8,  85, 249, 240, 136,   9, 215, 166,
  185, 170, 191, 189, 224, 138, 186, 110,
  154, 223, 201, 229, 135, 142, 164, 242,
  241, 234,  44, 227, 227,  54, 112, 210,
   17, 164, 172, 141, 213, 233,  10,  64,
   97, 202, 171,  97,  69, 255,  71,  89,
   67,  96, 249, 148, 172, 249,  24,  93,
  212, 171, 178,  40, 161, 179,  92,  32,    
    8,  85, 249, 240, 136,   9, 215, 166,
  185, 170, 191, 189, 224, 138, 186, 110,
  154, 223, 201, 229, 135, 142, 164, 242,
  241, 234,  44, 227, 227,  54, 112, 210,
   17, 164, 172, 141, 213, 233,  10,  64,
   97, 202, 171,  97,  69, 255,  71,  89,
   67,  96, 249, 148, 172, 249,  24,  93,
  212, 171, 178,  40, 161, 179,  92,  32,    
};
const size_t testW = 8;
const size_t testH = 16;
const char* testMsg = "A secret message";

#define NUM_BITS_PER_CHAR (8)
#define CHAR_SIZE (sizeof(char) * NUM_BITS_PER_CHAR)

#define LSB_BITS         (2)
#define LSB_MASK         ((1u << (LSB_BITS))-1)
#define LSB_MASK_CLEAR   (~(LSB_MASK))

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// SOLUTION STARTS HERE
bool Encode(uint8_t* raster, const size_t w, const size_t h, const char *text)
{
  if (!raster || !text || !w || !h)  {
      printf("input error !\n");
      return false;
  }

  uint32_t image_size = (w * h);
  uint32_t text_size_bits = (strlen(text)+1)*NUM_BITS_PER_CHAR;

  // cannot fit text into the image
  if(image_size < ((text_size_bits + LSB_BITS - 1) / LSB_BITS)) {
      printf("Unable to fit text in raster.\n");
      return false;
  }
  
  printf("image size: %d\n", image_size);
  printf("text size : %d\n", text_size_bits);
  
  size_t text_idx = 0;

  for(size_t i=0; i < image_size && text_idx < text_size_bits; ++i) {
    printf("\toverwriting byte: %d\n",raster[i]);
    // nuke LSB_BITS from each byte
    raster[i] &= LSB_MASK_CLEAR;
    // extract LSB_BITS from text
    uint8_t out_bits = 0;
    for(int b=0; b<LSB_BITS; ++b) {
        uint8_t bit = (text[text_idx / 8] >> (text_idx % 8)) & 1;
        out_bits |= (bit << b);  // align to LSBs
        ++text_idx;
    }

    printf("overwriting bits: %d", out_bits);
    raster[i] |= out_bits;
    printf("\t\tnew byte: %d\n\n", raster[i]);
  }
  
  return true;
}
// SOLUTION ENDS HERE
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


// Contains unit test and harness
int main() {
  // testOutputExpected is based on replacing 2 LSBs
  // in each pixel.
  const uint8_t testOutputExpected[sizeof(testInput)] =
  {
    9, 84, 248, 241, 136, 8, 214, 164, 
    187, 168, 191, 189, 225, 137, 186, 109, 
    155, 220, 202, 229, 134, 140, 167, 241, 
    241, 233, 46, 225, 224, 53, 115, 209, 
    16, 164, 174, 140, 213, 235, 10, 65, 
    97, 201, 170, 97, 71, 252, 71, 89, 
    67, 96, 251, 149, 173, 248, 26, 93, 
    215, 169, 178, 41, 161, 177, 94, 33, 
    8, 84, 248, 240, 136, 9, 215, 166, 
    185, 170, 191, 189, 224, 138, 186, 110, 
    154, 223, 201, 229, 135, 142, 164, 242, 
    241, 234, 44, 227, 227, 54, 112, 210, 
    17, 164, 172, 141, 213, 233, 10, 64, 
    97, 202, 171, 97, 69, 255, 71, 89, 
    67, 96, 249, 148, 172, 249, 24, 93, 
    212, 171, 178, 40, 161, 179, 92, 32,   
  };
  
  uint8_t testOutputProvided[sizeof(testInput)];
  memcpy(testOutputProvided, testInput, sizeof(testOutputProvided));
  
  if (!Encode(testOutputProvided, testW, testH, testMsg)) {
    printf("Encode returned with an error");
    return -1;
  }

  printf("Provided Output:");

  bool success = true;
  for (uint32_t i = 0; i < sizeof(testOutputProvided); ++i)
  {
    if ((i % testW) == 0)
    {
      printf("\n");
    }
      
    if (testOutputProvided[i] != testOutputExpected[i])
    {
      printf("Got: %d (0x%x)  Expected: %d (0x%x) in element #%d",
             testOutputProvided[i], testOutputProvided[i], 
             testOutputExpected[i], testOutputExpected[i], i);
      success = false;
      break;
    }
    else
    {
      printf("%d, ", testOutputProvided[i] );
    }
  }
  
  printf("\n");

  if(success)
    printf("SOLUTION: SUCCEEDED\n");
  else
    printf("SOLUTION: FAILED\n");
  
  return 0;
}
