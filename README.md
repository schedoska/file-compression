# File Compresso/Decompressor

Project is compsed with two seperate applications. Coder allows to compress .pgm images using chosen prediction algorithm with Huffman coding technique. Decoder converts compressed file back to .pgm (P5) image. 

## Build

To build Koder and Dekoder appliactions, clone this repository and inside project directory use command 'make'.

## Coding

To compress .pgm file using Koder application:

```
.\Koder.exe [Path to .pgm image] [Path to output file] [Prediction mode] [Generate histograms (optional)]
```
* [Generate histograms] - argument is optional. If you add h argument in it's place, Coder application will generate 2 additional files containing histogram data of original input image "image.hist" and image after prediction algorithm stage "image_prediction.hist". This data can be used to define efectiveness of used algorithm.  
* [Prediction mode] - argument is obligatory. There you can choose prediction algorithm that will be used for compression:

| Argument | Prediction algorithm |
| ------ | ------ |
| L1 | Left neighbor |
| L2 | 2 Left neighbors |
| L3 | 3 Left neighbors |
| T1 | Top neighbor |
| T2 | 2 Top neighbors |
| T3 | 3 Top neighbors |
| M | Median value of top, left and left-top neighbors |
| G | Graham model |
| MED | MED/MAP predictor |
| LPC2 | Optimal linear prediction - rank 2 |
| LPC3 | Optimal linear prediction - rank 3 |
| LPC4 | Optimal linear prediction - rank 4 |
| LPC5 | Optimal linear prediction - rank 5 |
| LPC7 | Optimal linear prediction - rank 7 |
| LPC10 | Optimal linear prediction - rank 10 |

## Decoding 

Dekoder appliaction automatically detects used prediction algorithm. User needs to provide path to file that needs to ne decoded and output file path.

```
.\Dekoder.exe [Path to coded file] [Path to output .pgm image]
```

## Example

* Compression of image: boat.pgm to file.hu using Graham model algorithm 
```
.\Koder.exe boat.pgm file.hu G
```
* Decoding of file.hu back to .pgm image
```
.\Dekoder.exe file.hu Decoded.pgm
```