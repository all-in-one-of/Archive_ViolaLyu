from mocap_db import MoCapDB
import os
import random
from maya_proj_utils import MayaProjUtils
 
# Useage: Maya
# The output rib is saved in the project/RIB_Archive directory. 
#
# Malcolm Kesson
# Nov 11 2012
# Viola Lyu
# Mar 4 2016

class MoCapRMan(MoCapDB):
    def __init__(self, name, datapath, scaling):
        self.name = name
        self.begin = 1
        self.end = 1
        self.utils = None
        try:
            # Note the delayed import of MayaProjUtils.
            #from maya_proj_utils import MayaProjUtils
            self.utils = MayaProjUtils()
            self.archivepath = self.utils.getRIB_ArchivePath()
            if os.path.exists(self.archivepath) == False:
                os.mkdir(self.archivepath)
            self.begin = self.utils.getAnimationStart()
            self.end = self.utils.getAnimationEnd()
            self.scenename = self.utils.getSceneName()
        except:
            self.archivepath = os.path.dirname(datapath)
            self.scenename = 'untitled'
        MoCapDB.__init__(self, datapath, scaling)
        dataname = os.path.basename(datapath)
        self.dataname = dataname[:-4] # remove .txt
    # __________________________________________________
    def writePoints(self, trailMin, trailMax, step, width, taper, geoNum, numRand, jitter, rseed, cache):
        if self.__dataIsValid() == False:
            print('writePoints is valid')
            return ''
        current_frame = self.utils.getCurrentTime()
        begin,end = self.__getDataRange(trailMax)
        ribpath = self.__getRibPath('pnt',trailMax,step,width)
        # Reuse a previously computed rib archive...
        if self.__canReuse(ribpath,cache):
            return ribpath
        f = open(ribpath, 'w')
        f.write(self.__getRibHeader(begin,end))
        #f.write('Points "P" [')
        random.seed(rseed)
        for n in range(len(self.markers)):
            random.seed(rseed+n)
            diff = trailMax - random.uniform(trailMin, trailMax)
            data = self.getMarkerData(n,int(begin+diff),end,step)
            if len(data) == 0: # marker has no data for this frame
                continue
  
            r = random.uniform(1 - numRand, 1)
            tmpNum = float(geoNum) * r
            tmpNum = int(tmpNum)
            for nn in range(tmpNum):
                random.seed(rseed+n+nn)
                offset = random.uniform(-width, width)    
                count = 0
                for coord in data:
                    if count % 3 == 0:
                        f.write('Attribute "identifier" "float id" [%d]\n' % (count*100 + nn))
                        f.write('Points "P" [')
                    #if count == 0 or count % 15 == 0:
                        #f.write('\n\t')
                    f.write('%1.4f ' % (coord + offset + random.uniform(-jitter, jitter)) )
                    if count % 3 == 2:
                        tmp = 1.0 - (1.0 - float(count/3)/float(len(data)/3)) * taper
                        f.write('] "constantwidth" [%1.4f]\n' % (width*tmp))
                    count += 1
        f.close()
        return ribpath        
    # __________________________________________________
    # The curve type is catmull-rom because it guarantees the curve will pass
    # through the coordinates of the control vertices. However, the first and
    # last xyz coordinates must be repeated.
    def writeCurves(self, trailMin, trailMax, step, width, taper, geoNum, numRand, jitter, rseed, cache):
        if self.__dataIsValid() == False:
            return ''
        begin,end = self.__getDataRange(trailMax)
        # We need at least 4 cvs for a valid curve
        data_range = end - begin
        if data_range < 4:
            end = begin + 4
        
        ribpath = self.__getRibPath('cvs',trailMax,step,width)
        # Reuse a previously computed rib archive...
        if cache == 'Reuse' and os.path.exists(ribpath) == True:
            return ribpath
            
        f = open(ribpath, 'w')
        f.write(self.__getRibHeader(begin,end))
        f.write('AttributeBegin\n')
        f.write('\tBasis "catmull-rom" 1 "catmull-rom" 1\n')
        random.seed(rseed)
        for n in range(len(self.markers)):
            random.seed(rseed+n)
            # data is a simple list of coordinates [x,y,z,x,y,z etc...]
            diff = trailMax - random.uniform(trailMin, trailMax)
            data = self.getMarkerData(n,int(begin+diff),end,step)
            #if n == 0:
            #    print('marker %s had %d cvs' % (n, len(data)/3))
            # The marker has no data for this frame, go to the next marker.
            if len(data) == 0: 
                continue
            
            r = random.uniform(1 - numRand, 1)
            tmpNum = float(geoNum) * r
            tmpNum = int(tmpNum)
            
            for nn in range(tmpNum):
                # A "catmull-rom" generally has the first and last cvs repeated,
                # hence, we add 2 to the number of cvs.
                numcvs = (len(data)/3) + 2
                random.seed(rseed+n+nn)
                offset = random.uniform(-width, width)    
                #print('%1.3f' % offset)
                f.write('Attribute "identifier" "float id" [%d]\n' % (n*100 + nn))
                f.write('\tCurves "cubic" [%d] "nonperiodic" "P" [' % numcvs)
                # Repeat the first CV
                f.write('%1.4f %1.4f %1.4f ' % (data[0]+random.uniform(-jitter,jitter)+ offset,
                                                data[1]+random.uniform(-jitter,jitter)+ offset,
                                                data[2]+random.uniform(-jitter,jitter)+ offset) )
                count = 2
                for coord in data:
                    if count % 15 == 0:
                        f.write('\n\t\t')
                    f.write('%1.4f ' % (coord+random.uniform(-jitter,jitter)+ offset) )
                    count += 1
                # Repeat the last CV
                x,y,z = data[-3:]
                x += random.uniform(-jitter,jitter)+ offset
                y += random.uniform(-jitter,jitter)+ offset
                z += random.uniform(-jitter,jitter)+ offset
                f.write('%1.4f %1.4f %1.4f ' % (x,y,z) )
                #f.write('\n\t\t] "constantwidth" [%1.4f]\n' % width)
                #f.write('\n\t\t] "width" [%1.4f %1.4f %1.4f ]\n' % (width, width/2.0, width/5.0))
                f.write('\n\t\t] "width" [')
                for ct in range(numcvs - 2):
                    tmp = 1.0 - (1.0 - float(ct)/float(numcvs-2)) * taper
                    f.write('%1.4f ' % (width*tmp))
                f.write(']\n')
        f.write('AttributeEnd\n')
        f.close()
        return ribpath
    # __________________________________________________
    def writeBlobby(self, trail, step, width, cache, volume=False):
        if self.__dataIsValid() == False:
            return ''
        begin,end = self.__getDataRange(trail)
        geoname = 'blobS'
        if volume:
            geoname = 'blobV'
        ribpath = self.__getRibPath(geoname,trail,step,width)
        # Reuse a previously computed rib archive...
        if cache == 'Reuse' and os.path.exists(ribpath) == True:
            return ribpath
        
        f = open(ribpath, 'w')
        f.write(self.__getRibHeader(begin,end))
        alldata = []
        for n in range(len(self.markers)):
            data = self.getMarkerData(n,begin,end,step)
            if len(data) == 0:
                continue
            alldata.extend(data)
        numblobs = len(alldata)/3
        if volume:
            f.write('Blobby %d [8 \n' % numblobs)
        else:
            f.write('Blobby %d [\n' % numblobs)
        # Make each blob an ellipsoid and provide its array index.
        # The indices monotonously increment by 16.
        for n in range(numblobs):
            f.write('\t1001 %d\n' % (n * 16))
        # Add the blending code "0" and the number of blobs to blend.
        f.write('\t0 %d ' % + numblobs)
        # Specify the indices of all the blobs.
        for n in range(numblobs):
            f.write(' %d' % n)
        f.write(']\n\t[\n')
        for n in range(0, len(alldata), 3):
            x = alldata[n]
            y = alldata[n+1]
            z = alldata[n+2]
            f.write('\t')
            f.write('%1.4f 0 0 0  ' % width)
            f.write('0 %1.4f 0 0  ' % width)
            f.write('0 0 %1.4f 0  ' % width)
            f.write('%1.4f %1.4f %1.4f 1\n' % (x,y,z))
        f.write('\t] [""]\n')
        f.close()
        return ribpath
        
    # __________________________________________________
    # Given __getPadding(27), returns '0027'
    def __getPadding(self, frame):
        return '%0*d' % (4, frame)
    # __________________________________________________
    def __getRibPath(self,geoname,trail,step,geosize):
        frame = self.utils.getCurrentTime()
        pad = self.__getPadding(frame) 
        size = '%1.3f' % geosize # Avoid excessive trailing digits
        size = size.replace('.', '')
        ribname = '%s_%s.%s.rib' % (self.dataname, geoname,pad)
        path = os.path.join(self.archivepath, self.scenename)
        if os.path.exists(path) == False:
            os.mkdir(path)
        path = os.path.join(path, self.name)
        if os.path.exists(path) == False:
            os.mkdir(path)
        fullpath = os.path.join(path, ribname)
        return fullpath
    # __________________________________________________
    # Puts some useful information at the beginning of the rib archive file.    
    def __getRibHeader(self,begin,end):
        x,y,z,X,Y,Z = self.getFrameBbox(end) #self.getBbox()
        rib =  '#bbox: %1.4f %1.4f %1.4f %1.4f %1.4f %1.4f \n' % (x,y,z,X,Y,Z)
        rib += '# Data begin/end: %d to %d\n' % (begin,end)
        rib += '# Total number of mocap markers %d\n' % len(self.markers)
        rib += '# Total number of mocap frames %d\n' % self.frames
        return rib
    # __________________________________________________    
    def __getDataRange(self,trail):
        # Set a couple of reasonable default values for the data_begin/end.
        # self.begin and self.end are "read" from the "Frame Range" settings 
        # of Maya's Render Setting window - see the constructor.
        data_begin = self.begin - trail
        data_end = self.end
        if data_begin < 0:
            data_begin = 0;
        # Use Maya's values...
        if self.utils != None:
            current = self.utils.getCurrentTime()
            #print('current = %s\n' % current)
        #            if current == 1:
                # self.frames is defined in the base class. It's effectively 
                # number of frames of animation of the mocap performance.
#                data_end = self.frames
#                data_begin = 1
#            else:
            data_end = current
            if (current - trail) < 1:
                data_begin = 1
            else:
                data_begin = current - trail    
#                if (current + trail) > self.end:
#                    tmp = self.end - current
#                    if tmp >= 0:
#                        trail = tmp
#                data_begin = current - trail
#                if data_begin < 0:
#                    data_begin = current;
  
        return [data_begin,data_end]
    # __________________________________________________    
    def __dataIsValid(self):
        if len(self.getBbox()) == 0:
            return False
        return True
    # __________________________________________________    
    def __canReuse(self,ribpath,cache):
        if cache == 'Reuse' or cache == 'reuse' and os.path.exists(ribpath) == True:
            return True
        return False