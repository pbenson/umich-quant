from os import listdir
from os.path import isfile, join
import pandas as pd
import csv

import mfmc as mc

if __name__ == '__main__':
    marketUniverse = mc.MarketUniverse()
    tickers = ['AAPL', 'NKE', 'GOOG']
    marketUniverse.initializeFromTickers(tickers)

    # create a Market
    startDate = mc.datetime64FromYYYYMMDD('20120101')
    endDate = mc.datetime64FromYYYYMMDD('20121231')
    decay = 0.97
    market = marketUniverse.marketForAllTickers(startDate, endDate, decay)

    # write a large number of simulations to a csv file
    with open('simulations.csv', 'w') as simOutputStream:
        simWriter = csv.writer(simOutputStream, delimiter='\t', quoting=csv.QUOTE_NONE)
        simWriter.writerow(market.tickers())
        numSims = 10000
        for i in range(1, numSims+1):
            if i % 1000 == 0:
                print 'completed simulation #'+str(i)
            sim = market.simulated_prices_list()
            simWriter.writerow(['{0:.2f}'.format(price) for price in sim])

    print "end of program"