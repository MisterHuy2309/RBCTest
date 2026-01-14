/*
* Need to tweak value of sensor and process noise
* arguments :
* process noise covariance
* measurement noise covariance
* estimation error covariance */
 
class Kalman_Filter_Distance {
protected:
    double _q; //process noise covariance
    double _q_init;
    double _r; //measurement noise covariance
    double _r_init;
    double _x; //value
    double _p; //estimation error covariance
    double _p_init;
    double _k; //kalman gain
 
public:
    /*
* Need to tweak value of sensor and process noise
* arguments :
* process noise covariance
* measurement noise covariance
* estimation error covariance */
    Kalman_Filter_Distance(double q, double r, double p)
        : _q(q)
        , _q_init(q)
        , _r(r)
        , _r_init(0)
        , _x(0)
        , _p(p)
        , _p_init(p)
        , _k(_p / (_p + _r)){};
    virtual void init(double x) { _x = x; }
    virtual void setProcessNoiseCovariance(double i)
    {
        _q = i;
        _q_init = i;
    }
    virtual void setMeasurementNoiseCovariance(double i)
    {
        _r = i;
        _r_init = i;
    }
    virtual void setEstimatiomErrorCovariance(double i)
    {
        _p = i;
        _p_init = i;
    }
    virtual double kalmanUpdate(double measurement);
    virtual void reset()
    {
        _q = _q_init;
        _r = _r_init;
        _p = _p_init;
    };
};
 
double Kalman_Filter_Distance::kalmanUpdate(double measurement)
{
    //prediction update
    //omit _x = _x
    _p = _p + _q;
 
    //measurement update
    _k = _p / (_p + _r);
    _x = _x + _k * (measurement - _x);
    _p = (1 - _k) * _p;
 
    return _x;
}