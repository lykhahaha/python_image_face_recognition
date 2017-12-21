#include <simple_layers/simple_layer.h>  
#include <pluginlib/class_list_macros.h>  
#include <geometry_msgs/PointStamped.h>
#include <vector>
#include <math.h>

PLUGINLIB_EXPORT_CLASS(simple_layer_namespace::SimpleLayer, costmap_2d::Layer)  
      
using costmap_2d::LETHAL_OBSTACLE;  
      
namespace simple_layer_namespace  
{  
      
SimpleLayer::SimpleLayer() {}  
      
void SimpleLayer::onInitialize()  
{  
    ros::NodeHandle nh("~/" + name_), g_nh;  
 
    current_ = true;  
    odd=true;
    flag=false;
    num_line=0;
    dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);  
    dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(  
          &SimpleLayer::reconfigureCB, this, _1, _2);  
    dsrv_->setCallback(cb);  
    
    //subscribe the message geometry_msgs/PointStamped

    sub = g_nh.subscribe("/clicked_point",10,&SimpleLayer::pointMessageReceived, this);
}  
   
void SimpleLayer::pointMessageReceived(const geometry_msgs::PointStampedConstPtr& msg){

    if(odd == true){
        point= *msg;
        odd = false;
        line.clear();
        ROS_INFO_STREAM("Please choose the second point");
        flag=false;
    }
    else{
        double dist_line;
        x_dist=msg->point.x-point.point.x;
        y_dist=msg->point.y-point.point.y;
        dist_line=sqrt(x_dist*x_dist+y_dist*y_dist);
        num_point=ceil(dist_line/0.05);
        num_points.push_back(num_point);
        int i;
        for(i=0;i<=num_point;i++){
            zad.point.x=point.point.x+i*x_dist/num_point;
            zad.point.y=point.point.y+i*y_dist/num_point;
            line.push_back(zad); 
            flag=true;
        }
        lines.push_back(line);
        num_line=num_line+1;
        odd = true;
        ROS_INFO_STREAM("Succeed to add the virtual obstacle");
        }
}
      
void SimpleLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level){  
      
    enabled_ = config.enabled;  

}  
      
void SimpleLayer::updateBounds(double origin_x, double origin_y, double origin_yaw, double* min_x,  
                                               double* min_y, double* max_x, double* max_y){  
    if (!enabled_)  
       return;  
    //mark_x_ = origin_x + cos(origin_yaw);  
    //mark_y_ = origin_y + sin(origin_yaw);  
    mark_x_ = 1.0;  
    mark_y_ = 1.0;        
     // *min_x = std::min(*min_x, mark_x_);  
      //*min_y = std::min(*min_y, mark_y_);  
     // *max_x = std::max(*max_x, mark_x_);  
     // *max_y = std::max(*max_y, mark_y_);  
    //ROS_INFO_STREAM("Please choose the second point2");
}  
      
void SimpleLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i,  
                                              int max_j){  

    // if (!enabled_)  
    //     return;  
    //   //ROS_INFO_STREAM("Please choose the second point3");
    // int mx;  
    // int my;  
    // int i;
    //   //if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
    // if(odd==false){
    //     for(i=0;i<=10;i++){
    //         mx=line[i].point.x;
    //         my=line[i].point.y;	
    //         master_grid.setCost(mx, my, LETHAL_OBSTACLE);
    //     }
    // }  	
      //}  
	  if (!enabled_)  
    return;  
  unsigned int mx;  
  unsigned int my;  

    if(flag==true){
    	int j;
    	for(j=0;j<num_line;j++){
    	   int i;
    	   line=lines[j];
    	   num_point=num_points[j];
           for(i=0;i<=num_point;i++){
               mark_x_=line[i].point.x;
               mark_y_=line[i].point.y;	
               if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
               master_grid.setCost(mx, my, LETHAL_OBSTACLE);}
             
	       mark_x_=line[i].point.x;
               mark_y_=line[i].point.y+0.05;	
               if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
               master_grid.setCost(mx, my, LETHAL_OBSTACLE);}
              
	       mark_x_=line[i].point.x;
               mark_y_=line[i].point.y+0.05;	
               if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
               master_grid.setCost(mx, my, LETHAL_OBSTACLE);}
              
	       mark_x_=line[i].point.x+0.05;
               mark_y_=line[i].point.y+0.05;	
               if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
               master_grid.setCost(mx, my, LETHAL_OBSTACLE);}
           }
        }
    }

  // if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
  //   master_grid.setCost(mx, my, LETHAL_OBSTACLE);  
  // }  
  //   mark_x_ = 1.1;  
  //   mark_y_ = 1.1;     
  //   if(master_grid.worldToMap(mark_x_, mark_y_, mx, my)){  
  //   master_grid.setCost(mx, my, LETHAL_OBSTACLE);  
  // }  

} 
} // end namespace  
