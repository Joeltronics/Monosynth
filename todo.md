# TODOs

### General

* Come up with a name
* Clean up the GUI a bit/make it less ugly
* Use icons instead of text for GUI where it makes sense
* Possibly simplify a few features (particularly Mod 1)

### Front panel features not yet hooked up

* Noise
* Pitch mod
* Chorus & Reverb
* VCA overdrive
* Gate "click"
* The entire bottom section
  * Mono modes, glide, mod wheel, velocity
* A few individual controls that aren't hooked up

### Features not on front panel yet

* Another filter model
* "Under the hood" controls
* State saving & patch management
  * Move params into new class PatchState

### Quality

* Add quality setting
  * Determines upsampling, filter accuracy, possibly a few other things
* Improve filter algorithm
* Better analog-style VCO tuning drift
* Consistent volume across waveshapes & settings
  * Currently square wave sounds louder than other two
  * Gain knob is compensated
  * Compensate resonance volume drop
* Can hear "clicks" when VCA set to envelope
* Look into using higher internal upsampling
* Add oscillator waveshape imperfections

### Performance

* Fix eventBuf_t
  * Currently its just a std::vector, meaning can allocate memory during audio callback. This is bad!
  * Might be able to keep it as a vector, but would have to have some logic outside it to make sure it doesn't get bigger than allocated
* If receiving a larger block than expected from host, break into smaller blocks instead of reallocating
* Come up with linear alternative to OnePole for parameter smoothing
  * This will increase performance, as BufferOrVal will converge to being constant value faster
* Better downsampling filters
  * Use FIR filters (Need higher order, but better pipelining & can use SIMD)
  * This may also improve quality over current filters
* Look into using doubles for more of the audio pipeline
  * Doubles are already used within stages where it matters (e.g. the filter)
  * Other stages wouldn't benefit from extra precision, but may gain performance from not having to convert back & forth
  * On the other hand, may not gain performance, as processors can convert between double & float very quickly, and SIMD instructions are twice as effective over floats
* Use SIMD for more things that can be vectorized
  * Possibly even one-pole filters used in various places (vectorizing IIR filters is tricky but possible)
  * Even if not vectorizing one-pole filters, can process 2-4 in parallel
