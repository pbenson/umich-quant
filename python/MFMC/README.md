This is a multi-factor Monte Carlo implentation in Python 2. To use it, you will need data. From <a href="https://quantquote.com/historical-stock-data">QuantQuote</a>, you can download free S&P 500 historical prices, unzip it, and move the <code>daily</code> directory into your MFMC directory. 

The simulation is based on a method used by MSCI/RiskMetrics, originally described in <a href="http://pbenson.github.io/docs/rmm2q97.pdf">A general approach to calculating VaR without volatilities and correlations</a> (1997), and again in <a href="../docs/benson_zangari.pdf">Monte Carlo Simulation using the Benson-Zangari Approach</a> (2013).</p>

This project was originally <a href="https://pbenson.github.io/quant-projects/portfolio_modeling.html">written in C++</a>.
