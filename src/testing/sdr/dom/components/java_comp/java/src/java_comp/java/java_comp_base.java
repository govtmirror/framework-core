package java_comp.java;

import java.util.Properties;

import org.apache.log4j.Logger;

import org.omg.CosNaming.NamingContextPackage.CannotProceed;
import org.omg.CosNaming.NamingContextPackage.InvalidName;
import org.omg.CosNaming.NamingContextPackage.NotFound;
import org.omg.PortableServer.POAPackage.ServantNotActive;
import org.omg.PortableServer.POAPackage.WrongPolicy;

import CF.InvalidObjectReference;

import org.ossie.component.*;
import org.ossie.properties.*;

/**
 * This is the component code. This file contains all the access points
 * you need to use to be able to access all input and output ports,
 * respond to incoming data, and perform general component housekeeping
 *
 * Source: java_comp.spd.xml
 *
 * @generated
 */
public abstract class java_comp_base extends Component {
    /**
     * @generated
     */
    public final static Logger logger = Logger.getLogger(java_comp_base.class.getName());

    /**
     * The property app_id
     * If the meaning of this property isn't clear, a description should be added.
     *
     * @generated
     */
    public final StringProperty app_id =
        new StringProperty(
            "app_id", //id
            null, //name
            null, //default value
            Mode.READONLY, //mode
            Action.EXTERNAL, //action
            new Kind[] {Kind.CONFIGURE} //kind
            );

    /**
     * The property number_components
     * If the meaning of this property isn't clear, a description should be added.
     *
     * @generated
     */
    public final ShortProperty number_components =
        new ShortProperty(
            "number_components", //id
            null, //name
            null, //default value
            Mode.READONLY, //mode
            Action.EXTERNAL, //action
            new Kind[] {Kind.CONFIGURE} //kind
            );
    
    /**
     * The property dom_id
     * If the meaning of this property isn't clear, a description should be added.
     *
     * @generated
     */
    public final StringProperty dom_id =
        new StringProperty(
            "dom_id", //id
            null, //name
            null, //default value
            Mode.READONLY, //mode
            Action.EXTERNAL, //action
            new Kind[] {Kind.CONFIGURE} //kind
            );
    
    /**
     * @generated
     */
    public java_comp_base()
    {
        super();

        // Properties
        addProperty(app_id);
        addProperty(number_components);
        addProperty(dom_id);
    }

    public void start() throws CF.ResourcePackage.StartError
    {
        super.start();
    }

    public void stop() throws CF.ResourcePackage.StopError
    {
        super.stop();
    }

    /**
     * The main function of your component.  If no args are provided, then the
     * CORBA object is not bound to an SCA Domain or NamingService and can
     * be run as a standard Java application.
     * 
     * @param args
     * @generated
     */
    public static void main(String[] args) 
    {
        final Properties orbProps = new Properties();
        java_comp.configureOrb(orbProps);

        try {
            Component.start_component(java_comp.class, args, orbProps);
        } catch (InvalidObjectReference e) {
            e.printStackTrace();
        } catch (NotFound e) {
            e.printStackTrace();
        } catch (CannotProceed e) {
            e.printStackTrace();
        } catch (InvalidName e) {
            e.printStackTrace();
        } catch (ServantNotActive e) {
            e.printStackTrace();
        } catch (WrongPolicy e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }
}
