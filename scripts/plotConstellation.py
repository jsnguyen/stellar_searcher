#!/usr/local/bin/python3

import argparse
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.basemap import Basemap

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('filename', type=str, help='input constellation filename')

args = parser.parse_args()
__FILENAME__ = args.filename

ra=[]
dec=[]
with open(__FILENAME__) as f:
    for line in f:
        l = line.strip().split()[2][1:-1].split(',')
        print(l)
        ra.append(float(l[0]))
        dec.append(float(l[1]))

margin = 6
lon_min = min(ra) - margin
lon_max = max(ra) + margin
lat_min = min(dec) - margin
lat_max = max(dec) + margin
print(lon_min,lon_max)
print(lat_min,lat_max)

m = Basemap(llcrnrlon=lon_min,
            llcrnrlat=lat_min,
            urcrnrlon=lon_max,
            urcrnrlat=lat_max,
            lon_0=np.mean(ra),
            lat_0=np.mean(dec),
            projection='gnom',
            )

parallels = np.linspace(lat_min,lat_max,6)
meridians = np.linspace(lon_min,lon_max,6)

m.drawparallels(parallels,labels=[False if i%2 else True for i,_ in enumerate(parallels)],labelstyle='+/-')
m.drawmeridians(meridians,labels=[True if i%2 else False for i,_ in enumerate(meridians)],labelstyle='+/-')

lons, lats = m(ra,dec)
m.plot(lons,lats,marker='o',linestyle='-')
#m.plot(ra,dec,marker='o',linestyle='-')
plt.xlabel('Right Ascension [deg]',labelpad=30)
plt.ylabel('Declination [deg]',labelpad=70)
#print(ra,dec)
plt.tight_layout()
plt.show()
