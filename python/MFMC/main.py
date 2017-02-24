from os import listdir
from os.path import isfile, join
import pandas as pd

import mfmc as mc

if __name__ == '__main__':
    marketUniverse = mc.MarketUniverse()
    tickers = ['AAPL', 'NKE', 'GOOG']
    marketUniverse.initializeFromTickers(tickers)

    print "end of program"