# import pandas.io.data as web
import numpy as np
from pandas_datareader import data, wb
import historical_data as hd

if __name__ == '__main__':
    # spx = data.DataReader(name='USSPX', data_source='yahoo', start='2016-01-01')
    # tail = spx.tail()
    # spx['Close'].plot(figsize=(8,5))

    tickers = ['USSPX', 'AAPL', 'IBM', 'T', 'NKE', 'AMZN']
    tickerToLogReturns = {}
    for ticker in tickers:
        tickerDataFrame = data.DataReader(name=ticker, data_source='yahoo', start='2016-01-01')
        closePrices = tickerDataFrame['Close']
        tickerToLogReturns[ticker] =  np.log(closePrices / closePrices.shift(1))[1:]
    # aaplReturns.plot(figsize=(8,5))
    numReturns = len(tickerToLogReturns[tickers[0]])
    noiseSigma = 1.0 / np.sqrt(numReturns)
    noiseVector = np.random.normal(0, noiseSigma, numReturns)
    aaplReturns = tickerToLogReturns['AAPL'].values
    aaplSimulatedReturn = np.dot(aaplReturns, noiseVector)

    hd.get_snp500()

    print "program end"