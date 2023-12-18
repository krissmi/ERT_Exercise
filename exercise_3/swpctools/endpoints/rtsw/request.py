
import requests
from datetime import datetime
from typing import List
from collections import namedtuple
import logging

from . import exceptions


#
# RTSW Response Schema
#
class RtswSchema:

    Fields = ['time_tag',
              'speed', 'density', 'temperature',
              'bx', 'by', 'bz', 'bt',
              'vx', 'vy', 'vz',
              'propagated_time_tag']

    Record = namedtuple(typename='Record', field_names=Fields)
#
# RTSW Request Class
#
class RtswRequest:

    def __init__(self):
        self.logger = logging.getLogger(__name__)
        self.url = 'https://services.swpc.noaa.gov/products/geospace/propagated-solar-wind-1-hour.json'

    def verify_response_fields(self, resp_field_names: list) -> None:
        if resp_field_names == RtswSchema.Fields:
            return
        raise KeyError('response field names count is incorrect')

    def parse_float_field(self, field) -> float:
        try:
            return float(field)
        except TypeError:
            return 0.0
        except ValueError:
            return 0.0

    def parse_integer_field(self, field) -> int:
        try:
            return int(field)
        except TypeError:
            return 0
        except ValueError:
            return 0

    def parse_datetime_field(self, field) -> datetime:
        try:
            return datetime.strptime(field, '%Y-%m-%d %H:%M:%S.%f')
        except TypeError:
            raise exceptions.RtswFieldConversionError('failed to convert date/time field')
        except ValueError:
            raise exceptions.RtswFieldConversionError('failed to convert date/time field')

    def parse_response_fields(self, resp_data: List[List]) -> List[namedtuple]:
        parsed = []

        for data in resp_data:
            record = RtswSchema.Record(
                self.parse_datetime_field(data[0]),     # time_tag
                self.parse_float_field(data[1]),        # speed
                self.parse_float_field(data[2]),        # density
                self.parse_float_field(data[3]),        # temperature
                self.parse_float_field(data[4]),        # bx
                self.parse_float_field(data[5]),        # by
                self.parse_float_field(data[6]),        # bz
                self.parse_float_field(data[7]),        # bt
                self.parse_float_field(data[8]),        # vx
                self.parse_float_field(data[9]),        # vy
                self.parse_float_field(data[10]),       # vz
                self.parse_datetime_field(data[11])     # propagated_time_tag
            )
            parsed.append(record)

        return parsed

    def records(self) -> List[namedtuple]:
        self.logger.info('endpoint: %s', self.url)
        response = requests.get(self.url)
        if not response.ok:
            response.raise_for_status()
        data = response.json()
        self.logger.debug('response: %s', response.json())

        self.verify_response_fields(resp_field_names=data[0])

        parsed = self.parse_response_fields(resp_data=data[1:])

        return parsed

# END-OF-FILE
