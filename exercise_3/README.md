## <ins>Data Collection</ins>

You have been assigned to write an app that collects data from an outside source. The source is from the 
NOAA Space Weather Prediction Center (SWPC)  and the data is the  Real-Time Solar Wind (RTSW) from the 
NOAA/DSCOVR satellite. 

The source is available at: <https://services.swpc.noaa.gov/products/geospace/propagated-solar-wind-1-hour.json> 

1. Develop an application and/or associated with Application Programming Interfaces (APIs), in Python 3, that 
   will download RTWS data. If you are asked to persist this data, how will you go about achieving this task? 
   Write a persistent layer with extensibility in mind. 
   - Be aware that you need to extend it to other different NOAA data sources. 
   - Pay attention to cadence, real-time requirements, and network constraints.
2. (Optional) Finally,  you are asked to containerize your app, please provide the appropriate necessary files, 
    that will allow running your app as a container,  in your favorite container runtime.
3. (Bonus: web-gui) You are now tasked with writing a dashboard that will provide early warning of solar storms, 
    you may use any web-based GUI framework, e., g React, Vue, angular, you wish to accomplish this task.
4. (Bonus: Machine Learning): Write a prediction engine that will try to forecast future space weather based on 
    past data. 
   - What was your preferred approach to this problem? 
   - Test it for some time, how would you go about comparing it to the real results?

## <ins>Research</ins>

- [Space Weather Live](https://www.spaceweatherlive.com/en/help/the-interplanetary-magnetic-field-imf.html)
- [Australian Space Weather Center](https://www.sws.bom.gov.au/Category/Solar/Solar%20Conditions/Solar%20Wind%20Clock%20Angle/Solar%20Wind%20Clock%20Angle.php)

## <ins>Thoughts</ins>

1. The container service could be expanded to include graphs and charts.
2. Machine learning is potentially a very large project in and of itself considering available data. [Apache Parquet](https://parquet.apache.org) was chosen as the data store format to support large data sets, analytics and various machine learning models.
3. The size of retreived data is a limiting factor in the current implementation.
4. The addition of new endpoints requires a code change.  This could be a configuration option with the addition of dynamic python package loading, etc.
5. Dependecy management is system specific (i.e. macOS) and could be expanded to be more platform agnostic.

## <ins>Dependencies</ins>

| module   | version | location                                                |
|----------|---------|---------------------------------------------------------|
| python   | 3.10.x  | <https://www.python.org/downloads/release/python-3100/> |
| requests | 2.31.0  | <https://docs.python-requests.org/en/latest/index.html> |
| pandas   | 2.1.4   | <https://pandas.pydata.org/docs/index.html>             |
| pyarrow  | 14.0.1  | <https://pypi.org/project/pyarrow/>                     |
| flask    | 3.0.0   | <https://flask.palletsprojects.com/en/3.0.x/>           |
| docker   | 24.0.x  | <https://www.docker.com>                                |
| colima   | 0.6.7   | <https://github.com/abiosoft/colima>                    |
| poetry   | 1.7.1   | <https://python-poetry.org/docs/>                       |
| numpy    | 1.26.2  | <https://numpy.org>                                     |
| waitress | 2.1.2   | <https://github.com/Pylons/waitress>                    |
| psutil   | 5.9.6   | <https://github.com/giampaolo/psutil>                   |

## <ins>Quick Start</ins>

1. Clone the repository to your local machine
`git clone https://github.com/krissmi/ERT_Exercise.git`

Once you have a local copy of the repository, there are 3 options:

2. Change to the exercise_3 directory
`cd ERT_Exercise/exercise_3`

### <ins>Repository based</ins>

3. The `swpctools.py` is available within the repository and may be executed by typing, at the root of
the cloned repository directory ($REPOROOT):
`./swpctools.py -h`.  

Detailed usage instructions can be found [here](#Usage)

### <ins>Package based</ins>

3. Build the package by typing:
`make package.build`

4. The new package is located in the `${REPOROOT}/dist` directory.  Install by typing:
`make package.install`

This will install it into the python sytem `${PYTHONLIB}/site-packages` directory. You may also install into any configured local environment using whatever commands are appropriate for your system.

The installed package may be removed with: `make package.remove`

Detailed usage instructions can be found [here](#Usage)

### <ins>Containerized</ins>

The exercise uses Docker (+ Colima on macOS) as it's application container host on the local system.  The image is built with default paramters but may be tweaked by modifying the Makefile commands.

3. Build the container with the following command:
`make service.build`

This command will create and configure a new image.

4. Spin up the container by typing:
`make service.run`

On successful startup, the application service is available at: `http://localhost:8000` using your favorite web browser.

5. The container may be stopped and removed with:
`make service.clean`

## <ins>Command Reference</ins>

The application module accepts command-line parameters of the form:
`swpctools <options> [endpoint] [action]`.

The _endpoint_ is one of many service endpoints defined for the NOAA Space Weather Prediction Center.  The
_action_ is type of request to the remote server with (optional) local processing.

### <ins>Common options</ins>

#### -h, --help

Displays usage information for application module.

#### -v, --verbose

Sets the module logger verbosity.

### <ins>Endpoints</ins>

#### as-local-service

Run the module as a foreground service accepting request on the the `localhost` at port `8080`.  This _endpoint_ is
special and includes actions for all remote service endpoints.

For example (installed package):
```
swpctools as-local-service
```

#### rtsw

Consumes records from the remote NOAA Real Time Solar Wind endpoint.

For example (installed package):
```
swpctools rtsw pull
```

### <ins>Endpoint Options</ins>

Service related commands accept the following flags/options

#### -h, --help

Displays usage information for a specific endpoint.

#### --datapath

Sets the data store file path.

For example (installed package):
```
swpctools [endpoint] [action] --datapath=/var/data/swpc
```

#### logspath

Sets the log files path.

For example (installed package):
```
swpctools [endpoint] [action] --logspath=/var/logs
```

### <ins>Endpoint Actions</ins>

#### pull

Pull records from the remote endpoint and update the local data store.

For example (installed package):
```
swpctools [endpoint] pull
```

#### dump

Pull records from the local data store, convert to CSV and write to the default console.

For example (installed package):
```
swpctools [endpoint] dump
```

### <ins>Endpoint Action Options</ins>

#### -h, --help

Displays usage information for a specific action.
