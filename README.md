# ModifiedAdaptiveTagentialCover
To install the program see <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/INSTALL.txt">INSTALL.txt</a> file


If you want you can also directly test the programm online:

http://ipol-geometry.loria.fr/~phuc/ipol_demo/PAMATC_IPOLDemo/


* [![Build Status](https://travis-ci.org/ngophuc/ModifiedAdaptiveTagentialCover.svg?branch=master)](https://travis-ci.org/ngophuc/ModifiedAdaptiveTagentialCover)

# Examples
<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/bird5.sdp">bird5.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATCSimplifiedDominantPoint -i ../Samples/bird5.sdp -o ../Results/bird5 -d ../ImaGene-forIPOL &#x000A;
./MATCSimplifiedDominantPoint -i ../Samples/bird5.sdp -o ../Results/bird5 -d ../ImaGene-forIPOL</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/bird5.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/bird5.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_ATC.png" alt="Adaptive Tagential Cover result" />
			</a>
		<br />
		ATC result
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_DPnew_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_DPnew_ATC.png" alt="Polygonal approximation with ATC" />
			</a>
		<br />
		Polygonalization with ATC
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_MATC.png" alt="Modified Adaptive Tagential Cover result" />
			</a>
		<br />
		MATC result
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_DPnew_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bird5_DPnew_MATC.png" alt="Polygonal approximation with MATC" />
			</a>
		<br />
		Polygonalization with MATC
		</td>		
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/leaf.sdp">leaf.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATCSimplifiedDominantPoint -i ../Samples/leaf.sdp -o ../Results/leaf -m 10 -s0.5 -d ../ImaGene-forIPOL &#x000A;
./MATCSimplifiedDominantPoint -i ../Samples/leaf.sdp -o ../Results/leaf -d -m 10 -s0.5 ../ImaGene-forIPOL</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/leaf.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/leaf.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_ATC.png" alt="Adaptive Tagential Cover result" />
			</a>
		<br />
		ATC result
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_DPnew_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_DPnew_ATC.png" alt="Polygonal approximation with ATC" />
			</a>
		<br />
		Polygonalization with ATC
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_MATC.png" alt="Modified Adaptive Tagential Cover result" />
			</a>
		<br />
		MATC result
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_DPnew_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/leaf_DPnew_MATC.png" alt="Polygonal approximation with MATC" />
			</a>
		<br />
		Polygonalization with MATC
		</td>		
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/bee.sdp">bee.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATCSimplifiedDominantPoint -i ../Samples/bee.sdp -o ../Results/bee -d ../ImaGene-forIPOL &#x000A;
./MATCSimplifiedDominantPoint -i ../Samples/bee.sdp -o ../Results/bee -d ../ImaGene-forIPOL</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/bee.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/bee.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_ATC.png" alt="Adaptive Tagential Cover result" />
			</a>
		<br />
		ATC result
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_DPnew_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_DPnew_ATC.png" alt="Polygonal approximation with ATC" />
			</a>
		<br />
		Polygonalization with ATC
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_MATC.png" alt="Modified Adaptive Tagential Cover result" />
			</a>
		<br />
		MATC result
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_DPnew_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/bee_DPnew_MATC.png" alt="Polygonal approximation with MATC" />
			</a>
		<br />
		Polygonalization with MATC
		</td>		
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/fly.sdp">fly.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATCSimplifiedDominantPoint -i ../Samples/fly.sdp -o ../Results/fly -m 10 -s 0.5 -d ../ImaGene-forIPOL &#x000A;
./MATCSimplifiedDominantPoint -i ../Samples/fly.sdp -o ../Results/fly -m 10 -s 0.5 -d ../ImaGene-forIPOL</code>
</pre>&#x000A;&#x000A;
<p>
	<table cellpadding="5">
		<tr>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/fly.png">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/fly.png" alt="Input image" />
			</a>	
		<br />
		Input image
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_ATC.png" alt="Adaptive Tagential Cover result" />
			</a>
		<br />
		ATC result
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_DPnew_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_DPnew_ATC.png" alt="Polygonal approximation with ATC" />
			</a>
		<br />
		Polygonalization with ATC
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_MATC.png" alt="Modified Adaptive Tagential Cover result" />
			</a>
		<br />
		MATC result
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_DPnew_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/fly_DPnew_MATC.png" alt="Polygonal approximation with MATC" />
			</a>
		<br />
		Polygonalization with MATC
		</td>		
		</tr>
	</table>
</p>

<p>File <a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Samples/Depth_P1_G3.sdp">Depth_P1_G3.sdp</a>: </p>&#x000A;&#x000A;
<pre class="code highlight js-syntax-highlight plaintext">
<code>./ATCSimplifiedDominantPoint -i ../Samples/Depth_P1_G3.sdp -o ../Results/Depth_P1_G3 -d ../ImaGene-forIPOL &#x000A;
./MATCSimplifiedDominantPoint -i ../Samples/Depth_P1_G3.sdp -o ../Results/Depth_P1_G3 -d ../ImaGene-forIPOL</code>
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
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_ATC.png" alt="Adaptive Tagential Cover result" />
			</a>
		<br />
		ATC result
		</td>	
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_DPnew_ATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_DPnew_ATC.png" alt="Polygonal approximation with ATC" />
			</a>
		<br />
		Polygonalization with ATC
		</td>		
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_MATC.png" alt="Modified Adaptive Tagential Cover result" />
			</a>
		<br />
		MATC result
		</td>
		<td align="center" valign="center">
			<a href="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_DPnew_MATC.pdf">
				<img width="150" src="https://github.com/ngophuc/ModifiedAdaptiveTagentialCover/blob/master/Results/Depth_P1_G3_DPnew_MATC.png" alt="Polygonal approximation with MATC" />
			</a>
		<br />
		Polygonalization with MATC
		</td>		
		</tr>
	</table>
</p>
