# sbugs

## Install CProcessor

```sh
$ cd src && ./install.sh
```

## Usage

```python
from CProcessor import PreProcessor

p = PreProcessor(inputfile, outfile, io=True)	
p.gen()
```

### Command line scripts in Examples
#### Pre-Processor
```sh
$ ./preProcessor.py -o <outfile> <inputfile>
$ ./preProcessor.py -h #Help
```
#### Test Generator
```sh
$ ./testGenerator.py -o <outfile> <inputfile>
$ ./testGenerator.py -h #Help
```

