# ModifiedAdaptiveTagentialCover
To install the program see <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/INSTALL.txt">INSTALL.txt</a> file


If you want you can also directly test the programm online:

http://ipol-geometry.loria.fr/~phuc/ipol_demo/PAMATC_IPOLDemo/


* [![Build Status](https://travis-ci.org/ngophuc/ModifiedAdaptiveTagentialCover.svg?branch=master)](https://travis-ci.org/ngophuc/ModifiedAdaptiveTagentialCover)

# Examples

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/Depth_P1_G3.sdp">Depth_P1_G3.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/Depth_P1_G3.sdp -o ../Results/Depth_P1_G3 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/Depth_P1_G3.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/Depth_P1_G3.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/AdaptativeTangentCover/blob/master/Results/Depth_P1_G3_ATC.png" alt="ATC result" />
			</a>
		<br />
		Adaptive Tagential Cover result
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_DPnew_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/AdaptativeTangentCover/blob/master/Results/Depth_P1_G3_DPnew_ATC.png" alt="ATC result" />
			</a>
		<br />
		Polygonal approximation with ATC
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/AdaptativeTangentCover/blob/master/Results/Depth_P1_G3_MATC.png" alt="MATC result" />
			</a>
		<br />
		Modified Adaptive Tagential Cover result
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_DPnew_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/AdaptativeTangentCover/blob/master/Results/Depth_P1_G3_DPnew_MATC.png" alt="MATC result" />
			</a>
		<br />
		Polygonal approximation with MATC
		</td>		
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/circle50.sdp">circle50.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/circle50.sdp -o ../Results/circle50 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/circle50.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/circle50.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50ATC.png" alt="ATC result" />
			</a>
		<br />
		ModifiedAdaptiveTagentialCover result
		</td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/circle50Noise4.sdp">circle50Noise4.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/circle50Noise4.sdp -o ../Results/circle50Noise4 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/circle50Noise4.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/circle50Noise4.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50Noise4.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50Noise4.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50Noise4ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circle50Noise4ATC.png" alt="ATC result" />
			</a>
		<br />
		ModifiedAdaptiveTagentialCover result
		</td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/AdaptativeTangentCover/blob/master/Samples/CircleRect.sdp">CircleRect.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/CircleRect.sdp -o ../Results/CircleRect -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/CircleRect.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/CircleRect.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>			
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/CircleRect.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/CircleRect.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circleRectATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/circleRectATC.png" alt="ATC result" />
			</a>
		<br />
		ModifiedAdaptiveTagentialCover result
		</td>
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/flower100Noise4.sdp">flower100Noise4.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATC_Computation -i ../Samples/flower100Noise4.sdp -o ../Results/flower100Noise4 -d ../ImaGene-forIPOL &#x000A;--maxScale 10 --samplingStep 1.0</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/flower100Noise4.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/flower100Noise4.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>			
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/flower100Noise4.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/flower100Noise4.png" alt="Input curve" />
			</a>	
		<br />
		Input curve
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/flower100Noise4ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/flower100Noise4ATC.png" alt="ATC result" />
			</a>
		<br />
		ModifiedAdaptiveTagentialCover result
		</td>
		</tr>
	</table>
</p>
