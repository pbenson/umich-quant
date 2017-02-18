# adapted from http://www.thealgoengineer.com/2014/download_sp500_data/

# note the change: from pandas.io.data import DataReader -> from pandas_datareader import data, wb
# may need to install tables module


import urllib2
import pytz
# import tables
import pandas as pd

from bs4 import BeautifulSoup
from datetime import datetime
# from pandas.io.data import DataReader
from pandas_datareader import data, wb


SITE = "http://en.wikipedia.org/wiki/List_of_S%26P_500_companies"
START = datetime(1900, 1, 1, 0, 0, 0, 0, pytz.utc)
END = datetime.today().utcnow()


def scrape_list(site):
    hdr = {'User-Agent': 'Mozilla/5.0'}
    req = urllib2.Request(site, headers=hdr)
    page = urllib2.urlopen(req)
    soup = BeautifulSoup(page,"html.parser")

    table = soup.find('table', {'class': 'wikitable sortable'})
    sector_tickers = dict()
    for row in table.findAll('tr'):
        col = row.findAll('td')
        if len(col) > 0:
            sector = str(col[3].string.strip()).lower().replace(' ', '_')
            ticker = str(col[0].string.strip())
            if sector not in sector_tickers:
                sector_tickers[sector] = list()
            sector_tickers[sector].append(ticker)
    return sector_tickers


def download_ohlc(sector_tickers, start, end):
    sector_ohlc = {}
    for sector, tickers in sector_tickers.iteritems():
        print 'Downloading data from Yahoo for %s sector' % sector
        dada = data.DataReader(tickers, 'yahoo', start, end)
        # for item in ['Open', 'High', 'Low']:
        #     dada[item] = dada[item] * dada['Adj Close'] / dada['Close']
        #     dada.rename(items={'Open': 'open', 'High': 'high', 'Low': 'low',
        #                    'Adj Close': 'close', 'Volume': 'volume'},
        #             inplace=True)
        #     dada.drop(['Close'], inplace=True)
        sector_ohlc[sector] = dada
    print 'Finished downloading data'
    return sector_ohlc


def store_HDF5(sector_ohlc, path):
    with pd.get_store(path) as store:
        for sector, ohlc in sector_ohlc.iteritems():
            store[sector] = ohlc


def get_snp500():
    sector_tickers = scrape_list(SITE)
    sector_ohlc = download_ohlc(sector_tickers, START, END)
    store_HDF5(sector_ohlc, 'snp500.h5')
