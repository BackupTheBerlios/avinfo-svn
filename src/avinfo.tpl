#AVInfo templates. http://shounen.ru/soft/avinfo/
#
#do not change without reading documentation
#
# first '#' in the line - comment
# [template name=tplname ver=1] - template header
# [head=XX] - head begin
# [body=XX] - body begin
# [foot=XX] - foot begin
#
[template name=default ver=1]
[body]
	if(ext="vob") print m1000:in; else print name;
	print ", ", m1024:size, "b";
	if(error){
		print " ",error," (!) \n";
		exit;
	}
	print "\n";
	set c=0;
	while (c++<stream.v) {
		print "video";
		if (stream.v>1) print c;
		print ": ";
		if (v[c].lang) print v[c].lang, " ";
		if (v[c].x&&v[c].y) print v[c].x, "x", v[c].y;
		if (v[c].aspectX&&v[c].aspectY) print "(",v[c].aspectX,":",v[c].aspectY,")";
		if (v[c].x&&v[c].y) print " ";
		if (v[c].fpsH) print v[c].fpsH;
		if (v[c].fpsH && v[c].fpsL) print ".", v[c].fpsL;
		if (v[c].fpsH) print "fps";
		if (v[c].cc) print " ", cn:v[c].cc;
		if (v[c].bps) print	 " ", m1000:v[c].bps, "bps";
		print "\n";
	}
	set c=0;
	while (c++<stream.a) {
		print "audio";
		if (stream.a>1) print c;
		print ": ";
		if (a[c].lang) print a[c].lang,  " ";
		if (a[c].freq) print m1000: a[c].freq, "Hz ";
		if (a[c].ch=2) print "Stereo ";
		if (a[c].ch=1) print "Mono ";
		if (a[c].ch>2) print  a[c].ch, " chanels ";
		if (a[c].bps) print m1000: a[c].bps,"bps";
		if (a[c].vbr) print "(VBR)";
		if (a[c].cc) print " ", cn: a[c].cc;
		print "\n";
	}
	set c=0;
	if(stream.t){
		print "text";
		if(stream.t>1) print "s";
		print ": ";
		while (c++<stream.t){
			if (t[c].lang) print t[c].lang; else print c;
			if(c<stream.t) print " + ";
		}
		print "\n";
	}
	set c=0;
	while (c++<stream.d) {
		set i=0;
		while (i++<d[c].num+1) {
			if( d[c][i].name&&d[c][i].value) print d[c][i].name, ": ", d[c][i].value, "\n";
		}
	}
[template name=description ver=1]
[body=128]
	print "\"", name, "\" ";
	if(error){
		print " ",error, " (!) \n";
		exit;
	}
	set c=0;
	if (a1.l) print ct:a1.l; else print v1.l;
	print " ";
	while (c++<stream.v) {
	    if (v[c].lang) print v[c].lang, "/";
		if (v[c].x&&v[c].y) print v[c].x, "x", v[c].y;
		if (v[c].aspectX&&v[c].aspectY) print "(",v[c].aspectX,":",v[c].aspectY,")";
		if (v[c].cc && v[c].x) print "/", cn:v[c].cc;
		if (v[c].bps) print "/", m1000: v[c].bps, "bps";
		if (v[c].fpsH && v[c].fpsH<18) print "/",v[c].fpsH,"fps";
	}
	print ", ";
	set c=0;
	while (c++<stream.a) {
	    if (a[c].lang) print a[c].lang;
		if (a[c].bps) print "/", m1000: a[c].bps, "bps";
   		if (a[c].cc) print "/",cn:a[c].cc;
		print ",";
	}
	set c=0;
	if(stream.t) print "sub:";
	while (c++<stream.t) {
			if (t[c].lang) print t[c].lang; else print c;
			if(c<stream.t) print "+";
		}
	print "\n";
[template name=list ver=1]
[head=78]
	print "\tFilelist generated by ",app.name, "(",app.ver,")", app.url, "\n\n";
[body=78]
	if(ext="vob"&&size<16000000) exit;
	if(ext="vob") print in; else print sn:name;
	if(ext!="ifo") print " ", m1024:size,"b"; 
	print "\t";
	if(error){
		print " ",error, " (!) \n";
		exit;
	}
	if ( (v1.x<512 || v1.y < 350 ) && v1.x && v1.y ) print v1.x,"x",v1.y, " ";
	if (v1.fpsH < 20 && v1.fpsH) print v1.fpsH,"fps ";
	if(v1.bps<500000 && v1.bps) print v1.bps, " ";

	if (stream.v>1) print "[",stream.v, "]";
	if (v1.x>511||v2.y>351) print v1.x,"x",v1.y;
	if (v1.aspectX && ((v1.x*v1.aspectX/v1.aspectY)-v1.y)) print "(",v1.aspectX,":",v1.aspectY,")";
	if (v1.l) print "/",ct: a1.l;
	if (v1.bps>500000) print "/",m1000: v1.bps,"bps";
	if (v1.cc && !(v1.cc=XVID || v1.cc=DIVX || v1.cc=DX50 || v1.cc=DIV3) ) print "/",cn: v1.cc;

	print " ";
	set c=0;
	if (stream.t) print "t:";
	while(c++<stream.t){
		if(t[c].lang) print t[c].lang; else print c;
		if(t[c+1].lang) print "+";
	}
	print " ";
	if (stream.a>1) print "[",stream.a,"]";
	set c=0;
	while(c++<stream.a){
		if(a[c].lang) print a[c].lang,",";
	}
	if (!v1.l&&a1.l) print ct:a1.l, "/";
	if (a1.freq) print m1000: a1.freq,"Hz";
	if (a1.bps) print "/", m1000: a1.bps,"bps";
	if (a1.cc) print "/",cn:a1.cc;
	if (a1.ch) print "/",a1.ch,"ch";
	print "\n";
[foot=78]
	print "\nStatistic: ",stat.total.files, " file(s), common length: ", ct:stat.total.length;
	print  ", common size: ";
	if(stat.total.size >10240)  print stat.total.size/1024, " Gb\n"; else print stat.total.size, " Mb\n";
	print "\tName\tBest\tWorst\t\n";
	if(stat.max.x||stat.min.x) print "\tHorizontal resolution:\t",stat.max.x,"\t",stat.min.x, "\n";
	if(stat.max.y||stat.min.y) print "\tVertical resolution:\t",stat.max.y,"\t",stat.min.y, "\n";	
	if(stat.min.fps||stat.max.fps) print "\tFPS\t",stat.max.fps,"\t",stat.min.fps,"\n";		
	if(stat.min.vidbps||stat.max.vidbps) print "\tVideo bitrate\t",m1000:stat.max.vidbps,"\t",m1000:stat.min.vidbps, "\n";
	if(stat.max.audbps) print "\tAudio bitrate\t",m1000:stat.max.audbps,"\t",m1000:stat.min.audbps, "\n";
	if(stat.max.freq) print "\tAudio sampling rate\t",m1000:stat.max.freq,"\t",m1000:stat.min.freq, "\n";
[template name=html-list ver=1]
[head]
	print "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n";
	print "<html>\n<head>\n\t<title>";
	print title, " (",run.year,"-",run.mon,"-",run.day,")</title>\n";
	print "<meta name=\"Description\" content=\"Automatically generated filelist\">\
	<meta name=\"Generator\" content=\"AVInfo 1.0 (http://shounen.ru/soft/avinfo/)\">\
	<style type=\"text/css\">\
		body{margin:1ex;padding:0}\
		table.report{width:100%;border-top:solid 1px gray;padding-top:1em}\
		td{padding:0.5ex;margin:0;border-bottom:dotted 1px silver}\
		.flnm{font-family:Tahoma;}\
		.fsize{font-family:Tahoma;font-weight:800;vertial-aligment:top}\
		.aud, .vid, {font-family:monospace}\
		.aud, .vid, .sub{font-size:90%}\
		.aud{color:#900;}\
		.vid{color:#009;}\
		.sub{color:#0A0;}\
		.bott{color:gray;font-size:90%;border-top:solid 1px silver;text-align:right;clear:both}\
	</style>\
</head>\
<body>\
	<h1>",title,"</h1>\n
	<p style=\"font-size:90%;font-family:Tahoma;color:gray;margin-left:1em\">created at <span style=\"color:green\">",run.year,"-",run.mon,"-",run.day,"</span>, ",run.hour,":",run.min,":",run.sec,"<br>",
	"<span style=\"color:orange;font-weight:800\">",stat.total.files, "</span> files, <span style=\"color:red;font-weight:800\">";
	if(stat.total.size>10240) print stat.total.size/1024,"</span> Gigabytes</p>";
		else print stat.total.size,"</span> Megabytes ";
	if(stat.total.length) print " (play time:",ct:stat.total.length,")";
	print "</p>";
	print "<table class=report cellpadding=0 cellspacing=0>\n";
[body]
	if(ext="vob"&&size<16000000) {exit;}
	print "<tr ";
	if( (counter / 4)*4=counter )
		print "style=\"background:#FFF5F5\"";
	else 
		if ((counter/4)*4+1=counter)  
			print "style=\"background:#F5FFF5\"";
		else
			if((counter/4)*4+2=counter)
				print "style=\"background:#F5F5FF\"";
	print "><td style=\"text-align:right\"><span class=\"flnm\">";
	if(ext="vob")print in; else print sn:name;
    print "</span><td class=fsize> &nbsp; ", m1024:size,"b";
	if(error){
		print "<td>"," ",error, " (!) \n";
		exit;
	}
	set c=0;
	print "<td><span class=\"vid\">";
	while (c++<stream.v) {
		print "video";
		if (stream.v>1) print c;
		print ": ";
		if (v[c].x&&v[c].y) print " ",v[c].x,"x", v[c].y;
		if (v[c].aspectX && ((v[c].x*v[c].aspectX/v[c].aspectY)-v[c].y)) print "(",v[c].aspectX,":",v[c].aspectY,")";
		if (v[c].fpsH) print ", ",v[c].fpsH,".",v[c].fpsL,"fps";
		if (v[c].cc) print ", ",cn: v[c].cc;
		if (v[c].bps) print ", ",m1000: v[c].bps,"bps",",";
		if (v[c].lang) print " language:", v[c].lang;
		print "<br>";
	}
	print "</span><span class=\"aud\">";
	set c=0;
	while (c++<stream.a){
		print "audio";
		if (stream.a>1) print c;
		print ": ";
		if (a[c].freq) print a[c].freq,"Hz";
		if (a[c].ch=2) print ", Stereo";
		if (a[c].ch=1) print ", Mono";
		if (a[c].ch>2) print a[c].ch," chanels";
		if (a[c].bps) print ", ",m1000: a[c].bps,"bps";
		if (a[c].vbr) print "(VBR)";
		if (a[c].lang) print " language: ", a[c].lang;
		print "<br>";
	}
	print "</span>";
	set c=0;
	print "<span class=sub>";
	while (c++<stream.t){
		print "subtitle";
		if(stream.t>1) print c;
		print ": ";
		if (t[c].lang) print t[c].lang; else print c;
		print "<br>";
	}
	print "</span>";
	set c=0;
	while (c++<stream.d) {
		set i=0;
		while (i++<d[c].num+1) if(d[c][i].name&&d[c][i].value) print d[c][i].name, ": ", d[c][i].value, " \n<br>";
	}
	print "</td>\n</tr>\n";
[foot]
	print "</table><hr>";
	print "<h2 style=\"text-align:center\">Statistic</h2>";
		print "</table><table align=center style=\"text-align:center;\">";
		print "<tr><td>Name<td>Best <td>Worst";
		if(stat.max.x||stat.min.x) print "<tr><td> Horizontal resolution:<td>",stat.max.x,"<td>",stat.min.x;
		if(stat.max.y||stat.min.y) print "<tr><td> Vertical resolution:<td>",stat.max.y,"<td>",stat.min.y;	
		if(stat.min.fps||stat.max.fps) print "<tr><td>FPS<td>",stat.max.fps,"<td>",stat.min.fps;		
		if(stat.min.vidbps||stat.max.vidbps) print "<tr><td>Video bitrate<td>",m1000:stat.max.vidbps,"<td>",m1000:stat.min.vidbps;
		if(stat.max.audbps) print "<tr><td>Audio bitrate<td>",m1000:stat.max.audbps,"<td>",m1000:stat.min.audbps;
		if(stat.max.freq) print "<tr><td>Audio sampling rate<td>",m1000:stat.max.freq,"<td>",m1000:stat.min.freq;
	print "</table>";
	print "<p class=bott>Generated by <a href=\"",app.url,"\">",app.name,"</a>, ",app.ver, "<br>\n";
	print"Scan duration:";
	if(run.scan.time) print run.scan.time; else print "&lt;1";
	print "s";
	if(stat.total.files/run.scan.time && run.scan.time>2 ) print " ( ",stat.total.files/run.scan.time, "files per sec)";
	print ", report duration:";
	if(run.report.time) print run.report.time;else print "&lt;1";
	print "s</p>\n";
	print "</body></html>";
[template name=short ver=1]
[body]
	print "\"",name,"\" ";
	if(error){
		print " ",error, " (!) \n";
		exit;
	}
	if (stream.v) print v1.x,"x",v1.y,", ";
	if(a1.l) print time:a1.l;
	if(!a1.l&&v1.l) print time:v1.l;
	if (!stream.v && stream.a) print a1.freq,"/", m1000: a1.bps,"bps";
	if (a[c].vbr) print "(VBR)";
	if (!stream.v && !stream.a && stream.t) print t1.lang;
	print "\n";
[template name=raw ver=1]
	print "***raw dump***\n";
	print "in=",in,"\n";
	print "shortname=",sn:name,"\n";
	print "size=",-1:size,"\n";
	print "hsize=",m1024:size,"\n";
	if(error) print "error=",error,"\n";
	if(stream.a) print "stream.a=",stream.a,"\n";
	if(stream.v) print "stream.v=",stream.v,"\n";
	if(stream.t) print "stream.t=",stream.t,"\n";
	if(stream.d) print "stream.d=",stream.d,"\n";
	if( stream.a ){
		set c=0;
		while(c++<stream.a){
			if( a[c].l ) print "a", c, ".l=", a[c].l,"\n";
			if( a[c].l ) print "a", c, ".len=", time:a[c].l,"\n";
			if( a[c].cc ) print "a", c, ".cc=", a[c].cc,"\n";
			if( a[c].cc ) print "a",c, ".codec=", fcc:a[c].cc,"\n";
			if( a[c].cc ) print "a",c, ".codecname=",cn:a[c].cc,"\n";
			if( a[c].ch ) print "a",c, ".ch=", a[c].ch,"\n";
			if( a[c].freq ) print "a",c, ".freq=", a[c].freq,"\n";
			if( a[c].bits ) print "a",c, ".bits=", a[c].bits,"\n";
			if( a[c].bps ) print "a",c, ".bps=", a[c].bps,"\n";
			if( a[c].vbr) print "a",c, ".vbr=",a[c].vbr,"\n";
			if( a[c].lang ) print "a",c, ".lang=", a[c].lang, "\n";
		}
	}
	if( stream.v ){
		set c=0;
		while(c++<stream.v){
			if( v[c].l ) print "v",c, ".l=", v[c].l,"\n";
			if( v[c].l ) print "v",c, ".len=", time:v[c].l,"\n";
			if( v[c].x ) print "v",c, ".x=", v[c].x,"\n";
			if( v[c].y ) print "v",c, ".y=", v[c].y,"\n";
			if( v[c].aspectX ) print "v",c, ".aspectX=", v[c].aspectX,"\n";
			if( v[c].aspectY ) print "v",c, ".aspectY=", v[c].aspectY,"\n";
			if( v[c].bits ) print "v",c, ".bits=", v[c].bits,"\n";
			if( v[c].cc ) print "v",c, ".cc=", v[c].cc,"\n";
			if( v[c].cc ) print "v",c, ".codec=", fcc:v[c].cc,"\n";
			if( v[c].cc ) print "v",c,".codecname=",cn:v[c].cc,"\n";
			if( v[c].fpsH ) print "v",c, ".fps=", v[c].fpsH;
			if( v[c].fpsH && v[c].fpsL ) print ".",v[c].fpsL;
			if( v[c].fpsH) print "\n";
			if( v[c].bps ) print "v", c, ".bps=", v[c].bps,"\n";	
			if( v[c].vbr) print "v", c,".vbr=", v[c].vbr,"\n";
			if( v[c].lang ) print "v",c, ".lang=", v[c].lang, "\n";
		}
	}
	if( stream.t ){
		set c=0;
		while(c++<stream.t){
			if(t[c].lang) print "t",c, ".lang=",t[c].lang, "\n";
		}
	}
	if( stream.d ){
		set c=0;
		while(c++<stream.d){
			if(d[c].num+1) print "d",c, ".num=",d[c].num,"\n";
			set i=0;
			while(i++<d[c].num){
				if(d[c][i].name) print "d",c, i, ".name=", d[c][i].name,"\n";
				if(d[c][i].value) print "d", c, i, ".value=", d[c][i].value,"\n";
			}
		}
	}
[template name=csv-list]
[head]
	print "filename;filesize;video;audio;subtitle;description";
[body]
	if(error){
		print " ",error, " (!) \n";
		exit;
	}
	if(ext="vob") print m1000:in; else print sn:name;
	print "; ", m1024:size, "b;";
	set c=0;
	if (stream.v>1) print "[",stream.v,"] ";
	while (c++<stream.v) {
		if (v[c].lang) print v[c].lang, " ";
		if (v[c].l) print time:v[c].l, " ";
		if (v[c].x&&v[c].y) print v[c].x, "x", v[c].y;
		if (v[c].aspectX&&v[c].aspectY) print "(",v[c].aspectX,":",v[c].aspectY,")";
		if (v[c].x&&v[c].y) print " ";
		if (v[c].fpsH) print v[c].fpsH;
		if (v[c].fpsH && v[c].fpsL) print ".", v[c].fpsL;
		if (v[c].fpsH) print "fps";
		if (v[c].cc) print " ", cn:v[c].cc;
		if (v[c].bps) print	 " ", m1000:v[c].bps, "bps";
		if(c<stream.v) print ", ";
	}
	print ";";
	set c=0;
	if (stream.a>1) print "[",stream.a,"] ";
	while (c++<stream.a) {
		if (a[c].lang) print a[c].lang,  " ";
		if (a[c].l) print time:a[c].l, " ";
		if (a[c].freq) print m1000: a[c].freq, "Hz ";
		if (a[c].ch=2) print "Stereo ";
		if (a[c].ch=1) print "Mono ";
		if (a[c].ch>2) print  a[c].ch, " chanels ";
		if (a[c].bps) print m1000: a[c].bps,"bps";
		if (a[c].vbr) print "(VBR)";
		if (a[c].cc) print " ", cn: a[c].cc;
		if(c<stream.a) print ", ";
	}
	print ";";
	set c=0;
	if (stream.t>1) print "[",stream.t,"] ";	
	while (c++<stream.t){
		if (t[c].lang) print t[c].lang; else print c;
		if(c<stream.t) print ", ";
	}
	print "; ";
	set c=0;
	while (c++<stream.d) {
		set i=0;
		while (i++<d[c].num+1) {
			if( d[c][i].name&&d[c][i].value) print d[c][i].name, "=", d[c][i].value;
			if(i<d[c].num+1&&d[c][i].name) print ", ";
		}
	}
[foot]
print "\n\n";
print ";;;;Generated by AVInfo 1.0, http://shounen.ru/soft/avinfo/\n\n";
print "\nStatistic;",total.files, " files; ",total.processed, " processed; ", "common length: ", ct:total.time, ";common size: ", total.size, "Gb","\n";
	  print "Min found:\n";
	  if ( total.minx && total.miny ) print " video: ;", total.minx,"x",total.miny, " ;";
	  if ( total.minfps ) print " ", total.minfps, "fps ;";
	  if ( total.minvbps ) print m1000:total.minvbps, "bps;\n";
	  if ( total.minabps||total.minfreq) print " audio: ;";
	  if ( total.minfreq) print m1000:total.minfreq, "Hz ;";
	  if ( total.minabps) print m1000:total.minabps, "bps;\n";
#the end
