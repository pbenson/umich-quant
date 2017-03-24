from os import listdir
from os.path import isfile, join
import pandas as pd

import mfmc as mc

if __name__ == '__main__':
    marketUniverse = mc.MarketUniverse()
    tickers = ['AAPL', 'NKE', 'GOOG']
    marketUniverse.initializeFromTickers(tickers)

    # test: create a MarketFactorVector
    marketFactor = marketUniverse.tickerToMarketFactorDict['GOOG']
    startDate = mc.datetime64FromYYYYMMDD('20120101')
    endDate = mc.datetime64FromYYYYMMDD('20121231')
    decay = 0.97
    mfv = mc.MarketFactorVector(marketFactor, startDate, endDate, decay)


    # create a Market
    tickerToMarketFactorDict = {'GOOG':marketFactor}
    market = mc.Market(tickerToMarketFactorDict, startDate, endDate, decay)
    sim = market.simulation()


    print "end of program"