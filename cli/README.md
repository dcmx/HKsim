
# Hegselmann-Krause Systems Simulation

## How to compile, run, and reproduce figures

 1. Check out repository.
 2. Install dependencies:
    - `# apt install python3-mpmath`
    - `# apt install python3-matplotlib`
    - `# apt install python3-networkx`
    - `# apt install gnuplot`
    - `# apt install texlive-full`
 3. Run:
	in the `cli` folder:
    - `$ python3 HKSMain.py > data.txt`
 4. Plot
    - `$ ./plot`
    usage: `plot [datafile i j]`
    The plot script plots the file `datafile` with values of n running from 4i to 4j in increments of four. Default values are `"data.txt" 3 15`. The resulting plots are stored as latex code in the figures folder. A preview is created in simple.pdf.
5. Preview figures
    - `$ xdg-open simple.pdf`

