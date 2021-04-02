from datetime import datetime,timedelta
import sys
import os

import mymail
import logging
import argparse

def checkarg():
        global symbol, subsymbol

        parser = argparse.ArgumentParser()

        parser.add_argument('-symbol',action='store', help = " eg GCJ8 " )
        parser.add_argument('-subsymbol',action='store', help = " eg GC " )

        args = parser.parse_args()
        symbol=args.symbol
        subsymbol=args.subsymbol


checkarg()
folder ='/mnt_data/arvin/intraday/'
newsymbol=str(subsymbol)+'1cmerevnew2 Comdty'

sdt=(datetime.today()).strftime('%Y%m%d')
d = datetime.strptime(sdt,'%Y%m%d')
cds=d.strftime('%Y%m%d')

cds='20210325'
print "cds = ",cds
pdt=(datetime.today()-timedelta(days=1)).strftime('%Y%m%d')
pd = datetime.strptime(pdt,'%Y%m%d')
pds=pd.strftime('%Y%m%d')

cds='20210324'
print "pds = ",pds

fn=folder+str(cds)+'/'+str(subsymbol)+'Pricelog.txt'

print "fn",fn

def gettlrt():
        return lastprint
        if t_lrt is None:
                return lrt[8:]
        elif lrt is None:
                return t_lrt[8:]
        else:
                return min(lrt[8:],t_lrt[8:])

def writeline():
        global prevseq,prevstr
        if ttq>0:

                if prevseq!=0:
                        of.write(prevstr)
                prevseq=seq
                prevstr=','.join((gettlrt(),newsymbol,bidq,str(bid),askq,str(ask),str(ltp),str(ttq)))+'\n'

if not os.path.isfile(fn) :
        raise ValueError('Input file not found for merge')
else:
        if not os.path.isdir(folder +str(cds)):
                os.system("mkdir "+folder +str(cds))
        ofn = folder+str(cds)+"/"+newsymbol+'.csv'
        f = open(fn)

        of = open(ofn,'w')
        bid =0.0
        ask = 0.0
        bidq='0'
        askq='0'
        ltp=0.0
        ttq=0
        lrt=''
        t_lrt=''
        pbid=0
        pask = 0
        lastprint=''
        seq=0
        prevseq=0
        prevstr=''

        trade_seq=[]
        processed_seq=[]
        l=f.readline()
        larr=l.split(',')
        if larr[0]==pds :
                while l:
                        lr=l.split(',')
                        if len(lr)>5 and lr[6]==symbol:
                                if lr[9]!='A' and lr[9]!='B':
                                        ttq+=int(lr[10])
                                        seq=lr[4]
                                        ltp= float(lr[9])*float(lr[13])
                                        t_lrt=lr[2]+lr[3]
                                        trade_seq.append(lr[4])
                                        if bid<ask:
                                                lastprint=t_lrt[8:]
                                                if seq not in processed_seq:
                                                        processed_seq.append(seq)
                                                writeline()
                                                pbid=bid
                                                pask = ask
                                if lr[9]=='A' or lr[9]=='B':
                                        seq=lr[4]
                                        lrt=lr[2]+lr[3]
                                        lpair=f.readline()
                                        lrpair=lpair.split(',')
                                        if len(lrpair)>5 and lrpair[6]==symbol and lrpair[2]+lrpair[3]==lrt:
                                                if lr[9]=='A' and lrpair[9]=='B':
                                                        bid=int(lrpair[10])*float(lrpair[12])
                                                        bidq=lrpair[11]
                                                        ask = int(lr[10])*float(lr[12])
                                                        askq=lr[11]
                                                elif lr[9]=='B' and lrpair[9]=='A':
                                                        ask=int(lrpair[10])*float(lrpair[12])
                                                        askq=lrpair[11]
                                                        bid = int(lr[10])*float(lr[12])
                                                        bidq=lr[11]
                                                if (pbid!=bid or pask !=ask) and bid<ask :
                                                        lastprint =lrt[8:]

                                                        if seq not in processed_seq:
                                                                processed_seq.append(seq)
                                                        writeline()
                                                        pbid = bid
                                                        pask = ask
                        l=f.readline()
        of.write(prevstr)

