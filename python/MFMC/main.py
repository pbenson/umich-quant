from os import listdir
from os.path import isfile, join
import pandas as pd

import mfmc as mc

if __name__ == '__main__':
    # print "hello"
    datafileDirectory = 'daily/'
    # dataFileNames = [f for f in listdir(datafileDirectory) if isfile(join(datafileDirectory, f))]
    dataFileNames = [f for f in listdir(datafileDirectory)]
    tickerToMarketFactorDict = {}
    fileCount = 0
    columnNames = [mc.DATE_TIME_COLUMN,'time','open','high','low',mc.CLOSE_COLUMN,'volume']
    for dataFileName in dataFileNames:
        fileCount += 1
        if fileCount > 3:
            break
        ticker = dataFileName[6:dataFileName.find('.')].upper()
        # print ticker
        data = pd.read_csv(datafileDirectory + dataFileName)
        data.columns = columnNames
        data[mc.DATE_TIME_COLUMN] = data[mc.DATE_TIME_COLUMN].apply(lambda x: mc.datetime64FromYYYYMMDD(x))
        for columnName in columnNames:
            if columnName != 'date' and columnName != 'close':
                data.drop(columnName, axis=1, inplace=True)
        tickerToMarketFactorDict[ticker] = mc.MarketFactor(ticker, data)

    # verify we can retrieve a MarketFactor via ticker
    aapl = tickerToMarketFactorDict['A']
    aaplMFV = mc.MarketFactorVector(aapl, mc.datetime64FromYYYYMMDD('20120103'),
                                    mc.datetime64FromYYYYMMDD('20121231'), 0.94)
    print "end of program"