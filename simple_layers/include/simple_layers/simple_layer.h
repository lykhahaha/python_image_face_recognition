    #ifndef SIMPLE_LAYER_H_  
    #define SIMPLE_LAYER_H_  
    #include <ros/ros.h>  
    #include <costmap_2d/layer.h>  
    #include <costmap_2d/layered_costmap.h>  
    #include <costmap_2d/GenericPluginConfig.h>  
    #include <dynamic_reconfigure/server.h>  
    #include <geometry_msgs/PointStamped.h>
    #include <vector>
    #include <math.h>
      
    using namespace std;
    using namespace geometry_msgs;

    namespace simple_layer_namespace  
    {  
      
    class SimpleLayer : public costmap_2d::Layer  
    {  
    public:  
      SimpleLayer();  
      
      virtual void onInitialize();  
      virtual void updateBounds(double origin_x, double origin_y, double origin_yaw, double* min_x, double* min_y, double* max_x,  
                                 double* max_y);  
      virtual void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);  
      void pointMessageReceived(const geometry_msgs::PointStampedConstPtr& msg);
    private:  
      void reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level);  
      ros::Subscriber sub;
      double mark_x_, mark_y_; 
      geometry_msgs::PointStamped point;
      geometry_msgs::PointStamped zad;
      vector<geometry_msgs::PointStamped> line;
      std::vector<vector<geometry_msgs::PointStamped> > lines;
      bool odd;
      bool flag;
      double x_dist, y_dist; 
      int num_line;
      int num_point;
      vector<int> num_points;
      dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig> *dsrv_;  
    };  
    }  
    #endif  