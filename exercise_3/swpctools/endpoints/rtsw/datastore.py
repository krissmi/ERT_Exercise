
import pandas as pd
import pyarrow as pa
import pyarrow.parquet as pq
from typing import List, NamedTuple
import logging
import io
from pathlib import Path

from . import exceptions


class RtswDataStore:

    def __init__(self, datafile: str = ''):
        self.logger = logging.getLogger(__name__)
        self.rtsw_filepath = datafile

    def info(self, frame: pd.DataFrame):
        buffer = io.StringIO()
        frame.info(buf=buffer)
        self.logger.debug(buffer.getvalue())

    def frame_from(self, dataset: List[NamedTuple]) -> pd.DataFrame:
        self.logger.info('translating raw data to dataframe')
        return pd.DataFrame(dataset)

    def to_csv(self, frame: pd.DataFrame) -> str:
        buffer = frame.to_csv()
        return buffer

    def to_csv_file(self, frame: pd.DataFrame, path: Path):
        self.logger.info('translating data frame to CSV file: {}'.format(path))
        frame.to_csv(path_or_buf=path)

    def write(self, frame: pd.DataFrame) -> None:
        self.logger.info('writing dataframe to: %s', self.rtsw_filepath)
        table = pa.Table.from_pandas(df=frame)
        pq.write_table(table=table, where=self.rtsw_filepath)

    def read(self) -> pd.DataFrame:
        try:
            self.logger.info('reading dataframe from: %s', self.rtsw_filepath)
            table = pq.read_table(self.rtsw_filepath)
            dataframe = table.to_pandas()
            return dataframe
        except FileNotFoundError:
            raise exceptions.RtswFieldDataFileNotFound

# END-OF-FILE
